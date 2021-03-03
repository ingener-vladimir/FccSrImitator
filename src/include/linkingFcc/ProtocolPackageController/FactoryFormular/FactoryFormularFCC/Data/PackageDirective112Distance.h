#ifndef PACKAGEDIRECTIVE112DISTANCE_H
#define PACKAGEDIRECTIVE112DISTANCE_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 112(Дистанция)
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "StructPackageDirective112Distance.h"

class PackageDirective112Distance : public BasePackage
{
    Header _header;
    QByteArray _array;

    static const uint8_t CODE_DISTANCE = 0b0010;  ///< Код признака дистанции

public:
    /*!
     * \brief Коснтруктор
     * \param msgNum Номер передаваемого сообщения
     * \param array Массив данных
     */
    PackageDirective112Distance(uint32_t msgNum,
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

#endif // PACKAGEDIRECTIVE112DISTANCE_H
