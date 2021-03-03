#ifndef PARSERAMPLIFIER_H
#define PARSERAMPLIFIER_H

/*!
    \file
    \brief Класс-наследник, реализующий парсинг параметров от Усилителя мощности
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "BaseParser.h"

class ParserAmplifier : public BaseParser
{

public:
    ParserAmplifier() {}
    ~ParserAmplifier() {}
    /*!
     * \brief Распарсить полученные данные
     * \param params Все параметры
     * \param obj Json с данными от устройства
     */
    void parseParams(const QJsonObject& obj) override;
};

#endif // PARSERAMPLIFIER_H
