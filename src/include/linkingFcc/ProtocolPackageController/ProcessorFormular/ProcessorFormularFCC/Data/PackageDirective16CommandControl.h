#ifndef PACKAGEDIRECTIVE16COMMANDCONTROL_H
#define PACKAGEDIRECTIVE16COMMANDCONTROL_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 16(Команда управления)
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IPackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "linkingFcc/infornation/CommandControl/BaseCommandControl.h"

#include <QSharedPointer>

class PackageDirective16CommandControl : public IPackage
{
    union
    {
        struct
        {
            daq::Header header;
            HeaderControlCommand command;
        } _data_block;
        uint8_t _data[sizeof(daq::Header) + sizeof(HeaderControlCommand)];
    };

public:
    PackageDirective16CommandControl(QByteArray& array);
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
    void unserialize(QSharedPointer<BaseCommandControl> commands);
};

#endif // PACKAGEDIRECTIVE16COMMANDCONTROL_H
