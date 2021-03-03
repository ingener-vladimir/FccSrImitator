#ifndef INETWORKWORKER
#define INETWORKWORKER

/*!
    \file
    \brief Интерфейсный класс для работы с массивом данных, полученных по сети
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QObject>
#include <QHostAddress>

class IPackageController;

class INetworkWorker: public QObject
{
    Q_OBJECT

public:
    virtual ~INetworkWorker(){}
    /*!
     * \brief Установить контролер пакетов
     */
    virtual void setController(QSharedPointer<IPackageController>) = 0;

    virtual void start() = 0;

public slots:
    /*!
     *  \brief Запись массива данных, используя ранее установленное подключение
     *  \param [in] byteArray Массив данных
    */
    virtual void writeDatagramm(const QByteArray &byteArray) = 0;
    /*!
     * \brief Чтение массива данных, полученных по ранее установленному подключению
     * \param[in] array Массив данных
     */
    virtual void readDatagramm(QByteArray& array) = 0;

signals:
    /*!
     * \brief Сигнал о завершении работы
     */
    void signalStopWork();

    void signalHostAddress(const QString& host);
};
#endif // INETWORKWORKER

