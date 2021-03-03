#ifndef PACKAGEDIRECTIVE98_H
#define PACKAGEDIRECTIVE98_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 98
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IPackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"

class PackageDirective98 : public IPackage
{
    Header _header;
     union
     {
         struct
         {
             daq::Header headerPkg;
         } _data_block;
         uint8_t _data[sizeof(daq::Header)];
     };

public:
     /*!
      * \brief Конструктор
      * \param array Массив данных
      */
    PackageDirective98(QByteArray& array);
    /*!
     * \brief Сериализует данные для отправки
     * \return Данные в виде массива байт
     */
    QByteArray serialize() override { return QByteArray(); }
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] array Полученные данные
     */
    void unserialize(QByteArray&) override;
};

#endif // PACKAGEDIRECTIVE98_H
