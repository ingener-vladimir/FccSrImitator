#ifndef PACKAGEDIRECTIVE112SPEED_H
#define PACKAGEDIRECTIVE112SPEED_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 112(Скорость)
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "StructPackageDirective112Speed.h"

class PackageDirective112Speed : public BasePackage
{
    Header _header;
    static const uint8_t CODE_SPEED = 0b0011;  ///< Код признака скорости

    union
    {
        struct
        {
            daq::Header headerPkg;
            PD112Speed structSpeed;
        } _data_block;
        uint8_t _data[sizeof(daq::Header) + sizeof(PD112Speed)];
    };

public:
    /*!
     * \brief Коснтруктор
     * \param msgNum Номер передаваемого сообщения
     * \param array Массив данных
     */
    PackageDirective112Speed(uint32_t msgNum,
                             QByteArray& array);
    /*!
     * \brief Сериализует данные для отправки
     * \return Данные в виде массива байт
     */
    QByteArray serialize() override;
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] array Полученные данные
     */
    void unserialize(QByteArray&) override {}
};

#endif // PACKAGEDIRECTIVE112SPEED_H
