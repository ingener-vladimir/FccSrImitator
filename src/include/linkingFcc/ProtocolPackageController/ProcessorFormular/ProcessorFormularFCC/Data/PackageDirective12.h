#ifndef PACKAGEDIRECTIVE12_H
#define PACKAGEDIRECTIVE12_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 12
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IPackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "linkingFcc/Structs/StructBandTLM.h"

class PackageDirective12 : public IPackage
{
    Header _header;
    union
    {
        struct
        {
            daq::Header headerPkg;
            BandTLM bandTLM;
        } _data_block;
        uint8_t _data[sizeof(daq::Header) + sizeof(BandTLM)];
    };

public:
    /*!
     * \brief Конструктор
     * \param array Массив данных
     */
    PackageDirective12(QByteArray& array);
    /*!
     * \brief Сериализует данные для отправки
     * \return Данные в виде массива байт
     */
    QByteArray serialize() override { return QByteArray(); }
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] array Полученные данные
     */
    void unserialize(QByteArray&) override {}

    uint16_t getData() const;
    uint32_t getTime() const;
};

#endif // PACKAGEDIRECTIVE16_H
