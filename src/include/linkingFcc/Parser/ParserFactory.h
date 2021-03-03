#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H

/*!
    \file
    \brief Класс-фабрика для создания объектов-парсеров
    \author Саньков Владимир
    \version 0.1
    \date декабрь 2019 г.
*/

#include "ParserModem.h"
#include "ParserAntenna.h"
#include "ParserAmplifier.h"
#include "ParserVirtual.h"
#include "ParserMeteo.h"

class ParserFactory
{
    QSharedPointer<IParserParams> _parser{nullptr}; ///< Указатель на парсера

public:
    ParserFactory(TypeKit type,
                  QSharedPointer<IJournal> journal = nullptr,
                  SenderParamsStation* sender = nullptr);
    ~ParserFactory();
    /*!
     * \brief Получить указатель на парсера
     * \return Указатель
     */
    QSharedPointer<IParserParams> getPtrParserParams();
};

#endif // PARSERFACTORY_H
