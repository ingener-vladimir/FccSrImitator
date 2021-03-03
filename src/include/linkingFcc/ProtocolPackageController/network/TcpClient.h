#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "TcpThreadSocket.h"
#include "TcpNetworkWorker.h"
#include "linkingFcc/ProtocolPackageController/ProtocolPackageController.h"
#include "linkingFcc/Senders/Ifc/IfcSenderFactory.h"

#include <QThread>

class TcpClient : public QObject
{
    Q_OBJECT
    quintptr _socketDescriptor;
    QString _hostAddress{""};
    quint16 _port;
    QSharedPointer<INetworkWorker> _networkWorker{nullptr};
    QSharedPointer<IPackageController> _packageController{nullptr};
    QSharedPointer<IIfcSender> _ifcSender{nullptr};
    QThread _thread;

    void stopWork();
    void process();
    void run();

public:
    TcpClient(qintptr handle, QSharedPointer<IPackageController> pkgController);
    TcpClient(QHostAddress address, quint16 port, QSharedPointer<IPackageController> pkgController);
    ~TcpClient();

    void start();
    void stop();

    QString getHostAddress() const;
    void setHostAddress(const QString &hostAddress);

    void setActive(const bool state);
    bool getIsActive() const;
    void sendIFCT();
signals:
    void signalStopWork(int des);
    void finished();
    void signalHostAddress(const QString& host);
};

#endif // TCPCLIENT_H
