#ifndef TCPNETWORKWORKER_H
#define TCPNETWORKWORKER_H

#include <thread>
#include <QThread>
#include <memory>
#include <QObject>
#include <QTimer>

#include "interface/linkingFcc/INetworkWorker.h"
#include "interface/linkingFcc/IPackageController.h"
#include "TcpThreadSocket.h"

class TcpNetworkWorker : public INetworkWorker
{
    Q_OBJECT

    QString _hostAddress{""};
    quint16 _port;
    std::unique_ptr<TcpThreadSocket> _client{nullptr};
    QSharedPointer<IPackageController> _controller{nullptr};
    QTimer _timerSend;

    void stopTimer();
    void work();

public:
    TcpNetworkWorker(qintptr desc, QSharedPointer<IPackageController> controller = nullptr);
    TcpNetworkWorker(QString host, quint16 port, QSharedPointer<IPackageController> controller = nullptr);
    ~TcpNetworkWorker();

    void setController(QSharedPointer<IPackageController> pkgCtrl) override;

    void start() override;

public slots:
    /*!
     *  \brief Запись массива данных,
     *  используя ранее установленное подключение
     *  \param [in] byteArray - массив данных
    */
    void writeDatagramm(const QByteArray &byteArray) override;
    /*!
     *  \brief Чтение массива данных
    */
    void readDatagramm(QByteArray &) override;
};

#endif // TCPNETWORKWORKER_H
