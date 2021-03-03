#ifndef PACKAGEDIRECTIVE03_H
#define PACKAGEDIRECTIVE03_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 03
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IPackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"

class PackageDirective03 : public IPackage
{
    QByteArray _arrayData;

public:
    /*!
     * \brief Конструктор
     * \param array Массив данных
     */
    PackageDirective03(QByteArray& array);
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

private:
    void writeTLM();
};

#endif // PACKAGEDIRECTIVE02_H
