#ifndef PACKAGEDIRECTIVE112ANGLE_H
#define PACKAGEDIRECTIVE112ANGLE_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 112(Угловые измерения)
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"
#include "StructPackageDirective112Angle.h"

class PackageDirective112Angle : public BasePackage
{
    Header _header;
    QByteArray _array;

    static const uint8_t CODE_AZIMUTH = 0b0110;  ///< Код признака азимута
    static const uint8_t CODE_ELEV = 0b0111;     ///< Код признака угла места

public:
    /*!
     * \brief Конструктор
     * \param msgNum Номер передаваемого пакета
     * \param array Массив данных
     * \param isAzimuth Флаг для выбора кода признака ИП
     */
    PackageDirective112Angle(uint32_t msgNum,
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

#endif // PACKAGEDIRECTIVE112ANGLE_H
