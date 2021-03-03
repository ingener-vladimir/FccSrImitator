#ifndef PARSERMETEO_H
#define PARSERMETEO_H

/*!
    \file
    \brief Класс-наследник, реализующий парсинг параметров от meteo устройства
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "BaseParser.h"

class ParserMeteo : public BaseParser
{

public:
    ParserMeteo() {}
    /*!
     * \brief Распарсить полученные данные
     * \param params Все параметры
     * \param obj Json с данными от устройства
     */
    void parseParams(const QJsonObject& obj) override;
};

#endif // PARSERVIRTUAL_H
