#include "linkingFcc/ProtocolPackageController/network/TcpNetworkWorker.h"

#include <QDebug>
#include <QThread>

TcpNetworkWorker::TcpNetworkWorker(qintptr desc, QSharedPointer<IPackageController> controller)
    : _controller(controller)
{
    _client = std::unique_ptr<TcpThreadSocket>(new TcpThreadSocket(desc));

    QObject::connect(_client.get(), &TcpThreadSocket::finished,
                     this, &TcpNetworkWorker::stopTimer);

    QObject::connect(&_timerSend, &QTimer::timeout,
                     this, &TcpNetworkWorker::work);
}

TcpNetworkWorker::TcpNetworkWorker(QString host, quint16 port, QSharedPointer<IPackageController> controller)
    : _hostAddress(host),
      _port(port),
      _controller(controller)
{
    _client = std::unique_ptr<TcpThreadSocket>(new TcpThreadSocket());

    QObject::connect(_client.get(), &TcpThreadSocket::finished,
                     this, &TcpNetworkWorker::stopTimer);

    QObject::connect(&_timerSend, &QTimer::timeout,
                     this, &TcpNetworkWorker::work);
}

TcpNetworkWorker::~TcpNetworkWorker()
{
    if(_client)
        _client->stop();
    _client.reset();
}

void TcpNetworkWorker::start()
{
    emit signalHostAddress(_client->hostAddress());
    _timerSend.start(100);
}

void TcpNetworkWorker::work()
{
    if(_client->socket().state() != QTcpSocket::ConnectedState)
    {
        _client->socket().abort();
        _client->socket().connectToHost(_hostAddress,_port);
        _client->socket().waitForConnected(100);
        qDebug()<<"try connect to " << _hostAddress << _port;
        return;
    }

    if(_controller)
    {
        QList<QByteArray> pack = _controller->getPackageList();
        for(auto iter : pack)
            writeDatagramm(iter);
    }

    if(_client)
    {
        QList<QByteArray> pack = _client->listData();
        for(auto iter : pack)
            readDatagramm(iter);
    }
}

void TcpNetworkWorker::writeDatagramm(const QByteArray &byteArray)
{
    if(_client && _client->isOpen()) {
        _client->send(byteArray);
        //qDebug() << "[SEND]" << byteArray;
    }
}

void TcpNetworkWorker::readDatagramm(QByteArray& array)
{
    if(_controller)
        _controller->appendPackage(array);
}

void TcpNetworkWorker::stopTimer()
{
    _timerSend.stop();
    emit signalStopWork();
}

void TcpNetworkWorker::setController(QSharedPointer<IPackageController> pkgCtrl)
{
    _controller = pkgCtrl;
}
