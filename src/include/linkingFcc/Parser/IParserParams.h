#ifndef IPARSERPARAMS_H
#define IPARSERPARAMS_H

/*!
    \file
    \brief Интерфейсный класс для парсинга параметров, получаемых от устройств
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include <QJsonObject>

#include "linkingFcc/Singleton/Singleton.h"
#include "linkingFcc/infornation/Params/ParamsCMS.h"

///< Типы комплектов
enum class TypeKit : uint8_t
{
    UNDEFINED = 0,
    MODEM = 1,
    CONVERTER_UP = 2,
    AMPLIFIER = 3,
    MSHY = 4,
    ANTENNA = 5,
    VIRTUAL = 6,
    CONVERTER_DOWN = 7,
    NP = 8,
    YAY495 = 9,
    TEST_TRANSLATION = 10,
    YAY374 = 11,
    POLAR_UP = 12,
    POLAR_DOWN = 13,
    METEOCOMPLEX = 14,
    SCU = 15
};

class IParserParams : public QObject
{

public:
    virtual ~IParserParams() = default;
    /*!
     * \brief Распарсить полученные данные
     * \param params Все параметры
     * \param obj Json с данными от устройства
     */
    virtual void parseParams(const QJsonObject& obj) = 0;
};

#endif // IPARSERPARAMS_H
