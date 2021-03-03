#include "linkingFcc/LinkingFCC.h"

#include <linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormular.h>
#include <linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormular.h>

#include "linkingFcc/ProtocolPackageController/ProtocolPackageController.h"

LinkingFCC::LinkingFCC()
{

}

void LinkingFCC::createServer(quint16 port, TypeFactory type)
{
    _guiExchangeAdapter = QSharedPointer<GUIExchangeAdapter>(new GUIExchangeAdapter());

    _server = std::unique_ptr<TcpServer>(new TcpServer(port, type));

    QObject::connect(_server.get(), &TcpServer::startConnection,
                     _guiExchangeAdapter.data(), &GUIExchangeAdapter::slotStartSendFunctionControl);

    QObject::connect(_server.get(), &TcpServer::closeConnection,
                     _guiExchangeAdapter.data(), &GUIExchangeAdapter::slotStopSendFunctionControl);

    QObject::connect(_server.get(), &TcpServer::sendMapConnection,
                     _guiExchangeAdapter.data(), &GUIExchangeAdapter::sendMapConnection);

    QObject::connect(_guiExchangeAdapter.data(), &GUIExchangeAdapter::signalSendIFCT,
                     _server.get(), &TcpServer::sendIFCT);

    QObject::connect(_guiExchangeAdapter.data(), &GUIExchangeAdapter::signalCloseAll,
                     _server.get(), &TcpServer::disconnectAllClients);

    QObject::connect(_guiExchangeAdapter.data(), &GUIExchangeAdapter::signalSendActive,
                     _server.get(), &TcpServer::setActiveClient);

    _server->start();
}

void LinkingFCC::createClient(QString host, uint16_t port, TypeFactory type)
{
    //инициалищация процессора и фабрики пакетов
    auto _processor = ProcessorFormular::createProcessorFormularClient(type);
    auto _factory = FactoryFormular::createFactoryFormular(type);

    if( _processor.isNull() || _factory.isNull())
    {
        qDebug()<<"[LinkingFCC::createServer]:: Null pounter detected";
        return;
    }

    _packageController = QSharedPointer<ProtocolPackageController>(new ProtocolPackageController(_factory, _processor));

    _client = std::unique_ptr<TcpClient>(new TcpClient(QHostAddress(host), port, _packageController));

    _client->start();
}

QSharedPointer<GUIExchangeAdapter> LinkingFCC::guiExchangeAdapter() const
{
    return _guiExchangeAdapter;
}

QSharedPointer<IPackageController> LinkingFCC::packageController() const
{
    return _packageController;
}
