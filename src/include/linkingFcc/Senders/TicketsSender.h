#ifndef DAQ_SENDERTICKETS_H
#define DAQ_SENDERTICKETS_H

#include "linkingFcc/infornation/Params/ParamsCMS.h"
#include "interface/linkingFcc/IJournal.h"

class SenderTickets
{
    QSharedPointer<IJournal> _journal{nullptr};

public:
    SenderTickets(QSharedPointer<IJournal> journal):_journal(journal) {}
    bool prepareTicketByteArray(const QJsonObject &object, ParamsCMS& params);
};

#endif // SENDERTICKETS_H
