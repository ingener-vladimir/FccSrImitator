#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QMap>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "TcpClient.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT

    quint16 _port;
    TypeFactory _typeFactory;

    QMap<qintptr, QSharedPointer<TcpClient>> _clients;

    QMap<uint16_t, qintptr> _mapConnection;
    static uint16_t connection;
    qintptr _prevDesc{0};

    void incomingConnection(qintptr handle) override;

    void deleteClient(int desc);

    void createMapConnection();

    // без этого никак, много подвязано
    QSharedPointer<GUIExchangeAdapter> _guiExchangeAdapter{nullptr};
public:
    TcpServer(quint16 port,TypeFactory type);
    ~TcpServer();

    void stop();
    void start();

    void setGuiExchangeAdapter(const QSharedPointer<GUIExchangeAdapter> &guiExchangeAdapter);

public slots:
    void onThreadedSocketFinished(int desc);
    void sendIFCT();
    void disconnectAllClients();
    void setActiveClient(const int number, const bool state);
    void slotStartConnction(const QString& host);

signals:
    void startConnection(const QString& host);
    void closeConnection(const QString& id);
    void sendMapConnection(const QJsonObject& object);
};

#endif // TCPSERVER_H
