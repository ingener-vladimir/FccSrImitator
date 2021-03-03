#ifndef PACKAGEDIRECTIVE150_H
#define PACKAGEDIRECTIVE150_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 150
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QString>

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"

class PackageDirective150 : public BasePackage
{
    Header _header;

public:
    PackageDirective150();
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

#endif // PACKAGEDIRECTIVE150_H
