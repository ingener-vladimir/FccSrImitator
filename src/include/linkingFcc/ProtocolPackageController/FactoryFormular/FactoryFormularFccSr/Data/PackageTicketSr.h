#ifndef PACKAGETICKET_H
#define PACKAGETICKET_H

/*!
    \file
    \brief Класс-наследник для создания квитанции
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"

class PackageTicketSr : public BasePackage
{
    HeaderSr _header;

public:
    /*!
     * \brief Коснтруктор
     * \param header Заголовок квитанции
     * \param msgNum Номер передаваемого сообщения
     */
    PackageTicketSr(HeaderSr& header, uint32_t msgNumber);
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

#endif // PACKAGETICKET_H
