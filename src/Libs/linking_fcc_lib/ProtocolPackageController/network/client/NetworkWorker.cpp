#include "linkingFcc/ProtocolPackageController/network/client/NetworkWorker.h"

NetworkWorker::NetworkWorker(QHostAddress reciveHost,
                             quint16 recivePort,
                             uint64_t interval):
    _reciveHost(reciveHost),
    _recivePort(recivePort),
    _ms_sleep(interval)
{

}

NetworkWorker::~NetworkWorker()
{
    _abort = true;
    _socketUdp.reset();
}

void NetworkWorker::setController(QSharedPointer<IPackageController> ctrl)
{
    _controller = ctrl;
}

void NetworkWorker::abort()
{
    _abort = true;
    emit finished();
}

void NetworkWorker::start()
{
    _abort = false;
}

void NetworkWorker::initThread()
{
    _abort = false;

    if(_socket == nullptr)
        _socket = std::unique_ptr<QTcpSocket>(new QTcpSocket());
    qDebug()<<"NetworkWorker::initThread() -> threadId = "<< QThread::currentThreadId();

    int64_t byte_write = 0;
    int64_t byte_read = 0;

    forever
    {
        if(_socket->state() != QTcpSocket::ConnectedState)
        {
            _socket->abort();
            _socket->connectToHost(_reciveHost,_recivePort);
            _socket->waitForConnected(200);
        }

        if(_controller)
        {
            QList<QByteArray> pack = _controller->getPackageList();
            for(auto iter : pack)
                writeDatagramm(iter);
        }

        if(_socket)
        {
//            QList<QByteArray> pack = _client->listData();
//            for(auto iter : pack)
//                readDatagramm(iter);

            while( _socket->bytesAvailable() > 0)
            {
                QByteArray datagram;
                datagram.resize(_socket->pendingDatagramSize());
                QHostAddress sender;
                quint16 senderPort;

                _socket->readDatagram(datagram.data(),
                                         datagram.size(),
                                         &sender,
                                         &senderPort);
                // qDebug()<<"NetworkWorker::readDatagramm Read size=" << datagram.size() <<" byte from host ="<<sender<<" port="<<senderPort;
                _controller->appendPackage(datagram);

                timeReadLastMsg = QDateTime::currentDateTimeUtc().currentMSecsSinceEpoch();
            }
        }

        if(_abort)
            break;
        if(_ms_sleep != 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(_ms_sleep));
    }

    Q_UNUSED(byte_read);
    Q_UNUSED(byte_write);

    emit signalStopWork();
}

void NetworkWorker::readDatagramm()
{
    int64_t ret = _socketUdp->bytesAvailable();
    while(_socketUdp->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(_socketUdp->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        _socketUdp->readDatagram(datagram.data(),
                                 datagram.size(),
                                 &sender,
                                 &senderPort);
        // qDebug()<<"NetworkWorker::readDatagramm Read size=" << datagram.size() <<" byte from host ="<<sender<<" port="<<senderPort;
        _controller->appendPackage(datagram);

        timeReadLastMsg = QDateTime::currentDateTimeUtc().currentMSecsSinceEpoch();
    }
    return ret;
}

int64_t NetworkWorker::writeDatagramm(const QByteArray &byteArray)
{
    if(_socketUdp != nullptr)
    {
        return _socketUdp->writeDatagram(byteArray,_sendHost,_sendPort);
       // qDebug()<<"NetworkWorker::writeDatagramm send byte" << ret << "byteArray size"<<byteArray.size() << _sendHost<<_sendPort;
    }
    return -1;
}


void NetworkWorker::setInterval(uint32_t val)
{
    _ms_sleep = val;
}

uint32_t NetworkWorker::getInterval()
{
    return _ms_sleep;
}

/*
 *   forever
    {
        QElapsedTimer elapsed;
        elapsed.start();
        workWithDevice();

        QCoreApplication::instance()->processEvents();

        if(_abort)
            break;

        // у устроства есть период опроса, вычислим на сколько нужно заснуть,
        // чтобы уложиться в тайминг. Период опроса - время текущих операций
//        int64_t tm = int64_t(_settings.getRequestTime()) - elapsed.elapsed();
       int64_t tm = 1000;
        if(tm > 0)
            QThread::msleep(uint64_t(tm));

        if(_abort)
            break;
    }
*/
