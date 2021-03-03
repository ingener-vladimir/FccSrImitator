#include "linkingFcc/ProtocolPackageController/network/TcpServer.h"

uint16_t TcpServer::connection = 0;

TcpServer::TcpServer(quint16 port,TypeFactory type)
{
    _typeFactory = type;
    _port = port;
    qDebug()<<"[TcpServer] : TcpServer create";
}

TcpServer::~TcpServer()
{
    qDebug()<<"[TcpServer] : TcpServer destroy";
    stop();
}

//Запуск сервера
void TcpServer::start()
{
    //Начинаем прослушивать порт
    if (!listen(QHostAddress::Any, _port))
        close();

    qDebug()<<"[TcpServer] : Start listen : QHostAddress::Any ; port = " <<_port;
}

//Остановка сервера
void TcpServer::stop()
{
    //Перестаем слушать порт, закрываем все сокеты
    if (isListening())
        close();

    foreach (auto it, _clients)
    {
        it.reset();
        it = nullptr;
    }
}

void TcpServer::incomingConnection(qintptr handle)
{
    deleteClient(handle);

    ++connection;
    QSharedPointer<TcpClient> client = QSharedPointer<TcpClient>(
                new TcpClient(handle, QSharedPointer<ProtocolPackageController>(
                                  new ProtocolPackageController(_typeFactory))));

    QObject::connect(client.data(), &TcpClient::signalHostAddress,
                     this, &TcpServer::slotStartConnction);

    QObject::connect(client.data(), &TcpClient::signalStopWork,
                     this, &TcpServer::onThreadedSocketFinished);

    _clients[handle] = client;
    _mapConnection[connection] = handle;
    client->start();
}

//Действия по окончании работы потока
void TcpServer::onThreadedSocketFinished(int desc)
{
    if(_clients.contains(desc))
    {
        emit closeConnection(_clients.value(desc)->getHostAddress());
        deleteClient(desc);
    }
}

void TcpServer::sendIFCT()
{
    for(auto& it : _clients.values())
    {
        if(it)
            it->sendIFCT();
    }
}

void TcpServer::disconnectAllClients()
{
    for(auto& desc : _clients.keys())
        onThreadedSocketFinished(desc);
}

void TcpServer::setActiveClient(const int number, const bool state)
{
    if(_mapConnection.contains(number))
    {
        auto desc = _mapConnection.value(number);
        if(_clients.keys().contains(desc))
        {
            if(_clients.contains(_prevDesc))
                _clients.value(_prevDesc)->setActive(false);

            _clients.value(desc)->setActive(state);
            createMapConnection();
        }
        _prevDesc = desc;
    }
}

void TcpServer::slotStartConnction(const QString &host)
{
    emit startConnection(host);
    createMapConnection();
}

void TcpServer::createMapConnection()
{
    QJsonObject object;
    QJsonArray array;

    for(auto& client : _clients.values())
    {
        if(client)
        {
            QJsonObject obj;
            obj.insert("address", QJsonValue(client->getHostAddress()));
            obj.insert("active", QJsonValue(client->getIsActive()));
            array.append(obj);
        }
    }
    object.insert("clients", array);
    emit sendMapConnection(object);
}

void TcpServer::setGuiExchangeAdapter(const QSharedPointer<GUIExchangeAdapter> &guiExchangeAdapter)
{
    _guiExchangeAdapter = guiExchangeAdapter;
}

void TcpServer::deleteClient(int desc)
{
    if(_clients.contains(desc))
    {
        auto client = _clients.value(desc);
        _clients.remove(desc);
        _mapConnection.remove(_mapConnection.key(desc));
        client.reset();
        client = nullptr;
        createMapConnection();
    }
}


