#include "linkingFcc/ProtocolPackageController/network/TcpThreadSocket.h"
#include "utils/NetworkPackageUtils.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <QDebug>

QTcpSocket &TcpThreadSocket::socket()
{
    return _socket;
}

TcpThreadSocket::TcpThreadSocket(quintptr socketDescriptor)
{
    _socket.setSocketDescriptor(socketDescriptor);

    int fd = _socket.socketDescriptor();
    _socket.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

    int maxIdle = 10; /* seconds */
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &maxIdle, sizeof(maxIdle));

    int count = 3;  // send up to 3 keepalive packets out, then disconnect if no response
    setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &count, sizeof(count));

    int interval = 2;   // send a keepalive packet out every 2 seconds (after the 5 second idle period)
    setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));

    QObject::connect(&_socket, &QTcpSocket::disconnected,
                     this, &TcpThreadSocket::stop);

    QObject::connect(&_socket, &QTcpSocket::connected,
                     this, &TcpThreadSocket::connected);

    QObject::connect(&_socket, &QTcpSocket::readyRead,
                     this, &TcpThreadSocket::onReadyRead);
}

TcpThreadSocket::TcpThreadSocket()
{
    int fd = _socket.socketDescriptor();
    _socket.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

    int maxIdle = 10; /* seconds */
    setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &maxIdle, sizeof(maxIdle));

    int count = 3;  // send up to 3 keepalive packets out, then disconnect if no response
    setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &count, sizeof(count));

    int interval = 2;   // send a keepalive packet out every 2 seconds (after the 5 second idle period)
    setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));

    QObject::connect(&_socket, &QTcpSocket::disconnected,
                     this, &TcpThreadSocket::stop);

    QObject::connect(&_socket, &QTcpSocket::connected,
                     this, &TcpThreadSocket::connected);

    QObject::connect(&_socket, &QTcpSocket::readyRead,
                     this, &TcpThreadSocket::onReadyRead);
}

TcpThreadSocket::~TcpThreadSocket()
{
    _socket.close();
}

void TcpThreadSocket::connected()
{
    buffer.clear();
}

void TcpThreadSocket::stop()
{
    buffer.clear();
    emit finished();
}

void TcpThreadSocket::send(const QByteArray &data)
{
    if(!data.isEmpty())
        _socket.write(data);
}

void TcpThreadSocket::onReadyRead()
{
    QMutexLocker lock(&_mutex);

    buffer += QByteArray(_socket.readAll());

    if(!buffer.isEmpty())
        qDebug() << "[TCP READ]" << buffer;

    static int faults = 0;
    while(buffer.contains((char)END_DATAGRAMM_SYMBOL))
    {
        auto datagram = NetworkPackageUtils::unescapeImcomingMessage(buffer.left(buffer.indexOf(END_DATAGRAMM_SYMBOL) + 1));
        if(!datagram.isEmpty())
        {
            if((uint8_t)datagram.at(0) == 0xC0 && datagram.size() > 21)
            {
                int dataL = ((uint8_t)datagram.at(20)<<8) | ((uint8_t)datagram.at(19));
//                qDebug() << "[TCP READ]" << dataL << datagram.size();
                if(datagram.size() == dataL + 22)
                {
                    _listData.append(datagram);
                    buffer = buffer.right(buffer.size() - buffer.indexOf(END_DATAGRAMM_SYMBOL) - 1);
                }
            } else
            {
                faults++;
                if(faults > 10)
                {
                    faults = 0;
                    buffer.clear();
//                    qDebug() << "[TCP READ] clearbuffer";
                }
            }
        }
    }
}

QList<QByteArray> TcpThreadSocket::listData()
{
    QMutexLocker lock(&_mutex);
    QList<QByteArray> copyList(_listData);
    _listData.clear();
    return copyList;
}
