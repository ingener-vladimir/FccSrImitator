#ifndef IPARAMSCONTROLLER_H
#define IPARAMSCONTROLLER_H

#include "linkingFcc/infornation/Params/ParamsCMS.h"
#include "linkingFcc/Journals/JournalCommon.h"

#include <QSharedPointer>

class IParamsController
{
public:
    virtual ~IParamsController() = default;
    /*!
     * \brief Установить новые параметры
     */
    virtual void setNewParams() = 0;
    virtual void setJournal(QSharedPointer<IJournal> journal) = 0;
};

#endif // IPARAMSCONTROLLER_H
