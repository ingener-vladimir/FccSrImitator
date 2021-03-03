#ifndef NETWORKWORKER_H
#define NETWORKWORKER_H

#include <QUdpSocket>
#include <QDateTime>
#include <QTcpSocket>

#include <thread>
#include <QThread>

#include "interface/linkingFcc/INetworkWorker.h"
#include "interface/linkingFcc/IPackageController.h"
#include "interface/linkingFcc/IPackage.h"

class NetworkWorker:public INetworkWorker
{
    Q_OBJECT

    std::unique_ptr<QTcpSocket> _socket = nullptr;
    QHostAddress _reciveHost;
    quint16 _recivePort;

    QHostAddress _sendHost;
    quint16 _sendPort;
    bool _isEnableRecive = false;
    bool _isEnableSend = false;
    uint64_t _ms_sleep;

    bool _abort = false;

    QSharedPointer<IPackageController> _controller = nullptr;

    int64_t timeReadLastMsg = 0;
public:
    NetworkWorker( QHostAddress reciveHost,
                   quint16 recivePort,
                   uint64_t interval = 100);
    virtual ~NetworkWorker();

    virtual void setController(QSharedPointer<IPackageController> ctrl) override;

    void abort();
    virtual void start() override;

    void setInterval(uint32_t val);
    uint32_t getInterval();


public slots:
    virtual void initThread();
    void writeDatagramm(const QByteArray &byteArray) override;
    void readDatagramm(QByteArray &) override;
};

#endif // NETWORKWORKER_H
