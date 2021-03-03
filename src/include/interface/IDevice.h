/*!
    \file
    \brief Интерфейсный класс для работы с устройствами

    \author Данильченко Артем
    \version 0.1
    \date декабрь 2018 г.
*/

#ifndef IDEVICE_H
#define IDEVICE_H

#include <QByteArray>
#include <QSharedPointer>
#include <QTcpSocket>
#include <QHash>
#include <stdint.h>
#include <QObject>

namespace daq
{

class IDeviceProtocol;

enum class DEV_CONDITION : uint8_t
{
    CONDITION_UNDEFINED            = 0,     ///< Неопределено
    CONDITION_HEALTHY              = 1,    ///< Исправен
    CONDITION_PARTIALLY_DEFECTIVE  = 2,    ///< Частично неисправен (работоспособен)
    CONDITION_UNHEALTHY            = 3,     ///< Неработоспособен
};


enum class DEV_CONNECTION_STATE
{
    NotConnected = 0,
    ConnectSuccessful,
    ConnectError
};

class IDevice
{
public:
    virtual  ~IDevice() {}

    /*!
     *   \brief Установка протокола взаимодействия с устройством
     *   IDeviceProtocol предоставляет интерфейс для формирования списка
     *   параметров для опроса/установки.
     *   \param[in] умный указатель на класс протокола взаимодействия
     */
    virtual void setDeviceProtocol(QSharedPointer<IDeviceProtocol>) = 0;

    /*!
     *   \brief Получение указателя на класс протокола взаимодействия
     *   с устройством.IDeviceProtocol предоставляет интерфейс
     *   для формирования списка параметров для опроса/установки.
     *   \return умный указатель на класс протокола взаимодействия
     */
    virtual QSharedPointer<IDeviceProtocol> getDeviceProtocol() = 0;

    /*!
     *   \brief Получение uuid устройства (задается при создании)
     *   \return уникальный id устроства
     */
    virtual QUuid deviceUuid() const =0;

    virtual void setImitMode(bool) = 0;
    /*!
     *   \brief Проверка - работает имитатор (NullDevice)
     *   или реальное устройство
     *   \return
     */
    virtual bool isImitDevice() = 0;

    /*!
     *   \brief Подключение к физическому устройству.
     *   \return результат операции
     */
    virtual bool connect(uint8_t addr,
                         const QString& ip,
                         uint16_t port,
                         uint16_t timeout = 1000) = 0;

    /*!
     * \brief Проверка состояние подключения
     * \return есть подключение или нет
     */
    virtual bool isConnected() = 0;

    /*!
     * \brief Проверка состояние подключения
     */
    virtual void disconnect() = 0;

    /*!
     *   \brief чтение параметров устройства
     *   \return обновляет состояние списка параметров
     */
    virtual bool getDeviceParametersValue() = 0;

    /*!
     *   \brief проверка на необходимость формирования
     *  прямого пакета данных для ядра
     *   \return нужно что-нибудь отсылать или нет
     */
    virtual bool isNeedDirectSendData() = 0;

    /*!
     *   \brief получение состояния устройства
     *   \return признак исправности :
     *  работоспособно, работоспособно с понижением
     *  характеристик, неработоспособно
     */
    virtual DEV_CONDITION getCondition() = 0;
};
}
#endif // IDEVICE_H
