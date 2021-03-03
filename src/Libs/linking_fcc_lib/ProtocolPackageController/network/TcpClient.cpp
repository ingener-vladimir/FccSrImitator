#include "linkingFcc/ProtocolPackageController/network/TcpClient.h"

TcpClient::TcpClient(qintptr handle, QSharedPointer<IPackageController> pkgController) :
    _socketDescriptor(handle),
    _packageController(pkgController)
{
    this->moveToThread(&_thread);
    QObject::connect(&_thread, &QThread::started,
                     this, &TcpClient::process);

    QObject::connect(this, &TcpClient::finished,
                     &_thread, &QThread::quit);

    qDebug()<<"[TcpClient] : TcpClient create";
}

TcpClient::TcpClient(QHostAddress address, quint16 port, QSharedPointer<IPackageController> pkgController) :
    _hostAddress(address.toString()),
    _port(port),
   _packageController(pkgController)
{
    this->moveToThread(&_thread);
    QObject::connect(&_thread, &QThread::started,
                     this, &TcpClient::run);

    QObject::connect(this, &TcpClient::finished,
                     &_thread, &QThread::quit);

    qDebug()<<"[TcpClient] : TcpClient create";
}

TcpClient::~TcpClient()
{
    if(_thread.isRunning())
    {
        _thread.quit();
        _thread.wait();
    }
    _packageController.reset();
    _packageController = nullptr;
    _networkWorker.reset();
    _networkWorker = nullptr;
    _ifcSender.reset();
    _ifcSender = nullptr;
    qDebug()<<"[TcpClient] : TcpClient destroy";
}

// для входящего соединения сервера
void TcpClient::process()
{
    if(!_networkWorker)
    {
        _networkWorker = QSharedPointer<INetworkWorker>(new TcpNetworkWorker(_socketDescriptor));
        _networkWorker->setController(_packageController);

        QObject::connect(_networkWorker.data(), &INetworkWorker::signalHostAddress,
                         this, &TcpClient::setHostAddress);

        QObject::connect(_networkWorker.data(), &INetworkWorker::signalStopWork,
                         this, &TcpClient::stopWork);

        _networkWorker->start();
    }

    if(!_ifcSender)
        _ifcSender = IfcSenderFactory::createIfcSender(_packageController);
}

// для создания непосредственно клиента, который цепляется к серверу
void TcpClient::run()
{
    if(!_networkWorker)
    {
        _networkWorker = QSharedPointer<INetworkWorker>(new TcpNetworkWorker(_hostAddress, _port));
        _networkWorker->setController(_packageController);

        QObject::connect(_networkWorker.data(), &INetworkWorker::signalHostAddress,
                         this, &TcpClient::setHostAddress);

        QObject::connect(_networkWorker.data(), &INetworkWorker::signalStopWork,
                         this, &TcpClient::stopWork);

        _networkWorker->start();
    }
}

void TcpClient::setActive(const bool state)
{
    if(_ifcSender)
        _ifcSender->setIsActive(state);
}

bool TcpClient::getIsActive() const
{
    if(_ifcSender)
        return _ifcSender->getIsActive();
    return false;
}

void TcpClient::start()
{
    _thread.start();
}

void TcpClient::stop()
{
    emit finished();
}

QString TcpClient::getHostAddress() const
{
    return _hostAddress;
}

void TcpClient::setHostAddress(const QString &hostAddress)
{
    _hostAddress = hostAddress;
    emit signalHostAddress(_hostAddress);
}

void TcpClient::sendIFCT()
{
    if(_ifcSender)
        _ifcSender->process();
}

void TcpClient::stopWork()
{
    stop();
    emit signalStopWork(_socketDescriptor);
}
