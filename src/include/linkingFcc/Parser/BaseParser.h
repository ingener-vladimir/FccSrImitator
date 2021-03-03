#ifndef BASEPARSER_H
#define BASEPARSER_H

/*!
    \file
    \brief Класс-наследник, имплементирующий функции парсинга
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "IParserParams.h"
#include "linkingFcc/Senders/ParamsStationSender.h"

class BaseParser : public IParserParams
{

public:
    explicit BaseParser(QSharedPointer<IJournal> journal = nullptr,
                        SenderParamsStation *sender = nullptr);
    ~BaseParser();

protected:
    ParamsCMS& params = ParamsSingleton::getInstance();
    QSharedPointer<IJournal> _journal{nullptr}; ///< Журнал регистарции событий
    SenderParamsStation* _sender{nullptr};
};

#endif // BASEPARSER_H
