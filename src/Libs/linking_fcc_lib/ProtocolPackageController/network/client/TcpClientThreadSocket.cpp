#include "linkingFcc/ProtocolPackageController/network/client/TcpClientThreadSocket.h"


TcpClientThreadSocket::TcpClientThreadSocket(QHostAddress reciveHost,
                     quint16 recivePort,
                     uint64_t interval)
{
    qDebug()<<"create UdpThread";

    _netThread = new QThread();
    _netWorker = new NetworkWorker( reciveHost,
                                    recivePort,
                                    interval
                                    );
    _netWorker->moveToThread(_netThread);
    QObject::connect(_netThread,SIGNAL(started()),_netWorker,SLOT(initThread()));
    QObject::connect(_netWorker,SIGNAL(signalStopWork()),_netThread,SLOT(quit()));
}

TcpClientThreadSocket::~TcpClientThreadSocket()
{
    if(_netThread->isRunning())
    {
        _netWorker->abort();
        _netThread->quit();
        _netThread->wait();
    }

    delete _netWorker;
    delete _netThread;

    qDebug()<<"delete TcpClientThreadSocket";
}


void TcpClientThreadSocket::run()
{
    if(_netThread && _netWorker)
        _netThread->start();
}

void TcpClientThreadSocket::stop()
{
    if(_netThread && _netWorker)
    {
        _netWorker->abort();
        _netThread->quit();
        _netThread->wait();
    }
}

void TcpClientThreadSocket::setController(IPackageController *ctrl)
{
    _netWorker->setController(ctrl);
}
