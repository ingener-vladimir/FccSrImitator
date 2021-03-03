#ifndef PACKAGEDIRECTIVE198_H
#define PACKAGEDIRECTIVE198_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 198
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"

class PackageDirective198 : public BasePackage
{
    Header _header;
    QByteArray _array;

public:
    /*!
     * \brief Коснтруктор
     * \param msgNum Номер передаваемого сообщения
     * \param array Массив данных
     */
    PackageDirective198(uint32_t msgNum,
                        Header& header,
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

#endif // PACKAGEDIRECTIVE198_H
