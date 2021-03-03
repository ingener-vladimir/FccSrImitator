#ifndef CONTROLCOMMAND_H
#define CONTROLCOMMAND_H

#include <stdint.h>
#include <QByteArray>
#include <QDataStream>
#include <QList>

#include "StructControlCommand.h"
#include "linkingFcc/Structs/Words.h"

class ControlCommandSr
{
    static const uint8_t COUNT_WORDS = 5;

    ControlCommands _number;            // номер КУ
    QList<uint16_t> _words;

public:
    ControlCommandSr();
    ControlCommandSr(const ControlCommands number);

    void addWords(uint16_t word, ...);
    uint16_t getValueWord(Words word);
    void setNumber(const ControlCommands &number);

    QByteArray serialize();
    void unserialize(StructControlCommand& header);
};

#endif // CONTROLCOMMAND_H
