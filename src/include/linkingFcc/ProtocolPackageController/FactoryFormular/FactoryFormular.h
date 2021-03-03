#ifndef FACTORYFORMULAR_H
#define FACTORYFORMULAR_H

/*!
    \file
    \brief Класс для создания объекта фабрики пакетов в зависимости от типа фабрики
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "FactoryFormularFCC/FactoryFormularFCC.h"
#include "FactoryFormularFccSr/FactoryFormularFccSr.h"

class FactoryFormular
{
    explicit FactoryFormular(TypeFactory type) = delete;
    FactoryFormular() = delete;
public:
    static QSharedPointer<IFactoryFormular> createFactoryFormular(TypeFactory type);
};

#endif // FACTORYFORMULAR_H
