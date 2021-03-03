#ifndef PACKAGEDIRECTIVE155_H
#define PACKAGEDIRECTIVE155_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 155
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "StructPackageDirective155.h"

class PackageDirective155 : public BasePackage
{
    Header _header;

    union
    {
        struct
        {
            daq::Header headerPkg;
            FunctionControl control;
        } _data_block;
        uint8_t _data[sizeof(daq::Header) + sizeof(FunctionControl)];
    };

public:
    PackageDirective155(uint32_t msgNum,
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

#endif // PACKAGEDIRECTIVE155_H
