#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include "NetworkWorker.h"
#include "interface/linkingFcc/IPackageController.h"

class  TcpClientThreadSocket : public QObject
{
    Q_OBJECT

    QThread* _netThread;
    NetworkWorker* _netWorker;

public:
    TcpClientThreadSocket(QHostAddress reciveHost,
              quint16 recivePort,
              uint64_t interval = 100);
    ~TcpClientThreadSocket();

    void run();
    void stop();

    void setController(IPackageController* ctrl);
};

#endif // UDPTHREAD_H
