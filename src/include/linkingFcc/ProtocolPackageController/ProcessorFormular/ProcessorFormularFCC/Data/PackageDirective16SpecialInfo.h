#ifndef PACKAGEDIRECTIVE16SPECIALINFO_H
#define PACKAGEDIRECTIVE16SPECIALINFO_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 16(Специальная информация)
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IPackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "linkingFcc/infornation/SpecialInformation/StructSpecialInformation.h"

class PackageDirective16SpecialInfo : public IPackage
{
    union
    {
        struct
        {
            daq::Header header;
            StructSpecialInformation specialInfo;
        } _data_block;
        uint8_t _data[sizeof(daq::Header) + sizeof(StructSpecialInformation)];
    };

public:
    /*!
     * \brief Конструктор
     * \param array Массив данных
     */
    PackageDirective16SpecialInfo(QByteArray& array);
    /*!
     * \brief Сериализует данные для отправки
     * \return Данные в виде массива байт
     */
    QByteArray serialize() override { return QByteArray(); }
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] array Полученные данные
     */
    void unserialize(QByteArray &) override;
};

#endif // PACKAGEDIRECTIVE16SPECIALINFO_H
