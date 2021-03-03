#ifndef PACKAGEDIRECTIVE16ONETIMECOMMAND_H
#define PACKAGEDIRECTIVE16ONETIMECOMMAND_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 16(Разовая командая)
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IPackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "linkingFcc/infornation/SingleCommand/SingleCommand.h"

class PackageDirective16OneTimeCommand : public IPackage
{
    union
    {
        struct
        {
            daq::Header header;
            PD116OneTimeCommand oneTimeCommand;
        } _data_block;
        uint8_t _data[sizeof(daq::Header) + sizeof(PD116OneTimeCommand)];
    };

public:
    /*!
     * \brief Конструктор
     * \param array Массив данных
     */
    PackageDirective16OneTimeCommand(QByteArray& array);
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
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] array Полученные данные
     */
    void unserialize(SingleCommand& commands);
};

#endif // PACKAGEDIRECTIVE16ONETIMECOMMAND_H
