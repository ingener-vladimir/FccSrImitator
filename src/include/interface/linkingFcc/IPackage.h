#ifndef IPACKAGE
#define IPACKAGE

/*!
    \file
    \brief Интерфейсный класс для работы с информационными пакетами
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QByteArray>
#include <QObject>

class IPackage
{

public:
    virtual ~IPackage() = default;
    /*!
     * \brief Сериализует данные для отправки
     * \return Данные в виде массива байт
     */
    virtual QByteArray serialize() = 0;
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] array Полученные данные
     */
    virtual void unserialize(QByteArray& array) = 0;

    /*!
     * \brief Вывод в консоль содержимого пакета
     * \author Данильченко Артем
     */
    virtual void toDebug(uint8_t){ }

};

#endif // IPACKAGE

