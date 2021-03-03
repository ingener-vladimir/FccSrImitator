#ifndef PARSERVIRTUAL_H
#define PARSERVIRTUAL_H

/*!
    \file
    \brief Класс-наследник, реализующий парсинг параметров от Виртуального устройства
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "BaseParser.h"

class ParserVirtual : public BaseParser
{

public:
    ParserVirtual() {}
    /*!
     * \brief Распарсить полученные данные
     * \param params Все параметры
     * \param obj Json с данными от устройства
     */
    void parseParams(const QJsonObject& obj) override;
};

#endif // PARSERVIRTUAL_H
