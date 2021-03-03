#ifndef SINGLECOMMANDSR_H
#define SINGLECOMMANDSR_H

#include <stdint.h>
#include <QByteArray>
#include <QDataStream>

#include "Periodicity.h"
#include "StructSingleCommand.h"

class SingleCommandSr
{
    Periodicity _periodecity; // тип разовой команды
    uint16_t _numberCommand;  // номер команды

public:
    SingleCommandSr(const Periodicity periodecity, const uint16_t numberCommand);
    SingleCommandSr() {}

    QByteArray serialize() const;
    void unserialize(StructSingleCommand& structSingleCommand);
};

#endif // SINGLECOMMANDSR_H
