#ifndef IPROTOCOL_H
#define IPROTOCOL_H

/*!
    \file
    \brief Интерфейсный класс для протокола
           взаимодействия с устройством          
    \author Данильченко Артем
    \version 0.1
    \date декабрь 2018 г.
*/

#include <QByteArray>
#include <QList>
#include <string>

namespace daq{

class IDevice;

/*!
  \details пока сделаем реализацию в каждом плагине.
  Когда плагин разделится на 2 части (форма и драйвер),
  реализацию нужно будет вынести в отдельную библиотеку
 */
class IDeviceProtocol
{
public:
    virtual ~IDeviceProtocol(){}

    virtual void setDevice(QSharedPointer<IDevice>) = 0;

    virtual QSharedPointer<IDevice> getDevice() = 0;

    /*!
     * \brief упаковать данные от устройства
     * в ИП в формате json для отправки  на запрос от ядра
     * \return результат упаковки
     */
     virtual bool serializeToAnswerIP(std::string &) = 0;

     /*!
     * \brief Формирование и упаковка данных для отправки
     * ИП от устройства. Инициатором является устройство
     * \return результат упаковки
     */
     virtual bool serializeToCtrlIP(std::string &) = 0;

     /*!
      * \brief Перепаковка ИП во внутренний формат устройства
      * \return массив для отправки по сети
      */
     virtual bool unserializeToDevice(const std::string &,
                                      std::string* answer = nullptr ) = 0;
};
}
#endif // IPROTOCOL_H
