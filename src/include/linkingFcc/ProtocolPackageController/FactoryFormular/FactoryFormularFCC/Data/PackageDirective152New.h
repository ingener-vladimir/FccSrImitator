#ifndef PACKAGEDIRECTIVE152NEW_H
#define PACKAGEDIRECTIVE152NEW_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 152 в новом формате
    \author Фуфаев Никита
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "StructPackageDirective152New.h"

class PackageDirective152New : public BasePackage
{
    Header _header;

    union
    {
        struct
        {
            daq::Header headerPkg;
            PD152New structTmi;
        } _data_block;
        uint8_t _data[sizeof(daq::Header) + sizeof(PD152New)];
    };

public:
    PackageDirective152New(uint32_t msgNum, const QByteArray& array);
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

#endif // PACKAGEDIRECTIVE152NEW_H
