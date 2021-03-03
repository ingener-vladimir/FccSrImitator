#include "linkingFcc/infornation/CommandControl/fcc-sr/ControlCommandSr.h"

ControlCommandSr::ControlCommandSr()
{
}

ControlCommandSr::ControlCommandSr(const ControlCommands number)
    : _number(number)
{
}

void ControlCommandSr::addWords(uint16_t word, ...)
{
    // установились на начало списка слов
    uint16_t *p = &word;
    int count{0};
    while (*p && count <= COUNT_WORDS)
    {
        _words.append(*p);
        p++;
        count++;
    }
}

uint16_t ControlCommandSr::getValueWord(Words word)
{
    if((uint8_t)word < _words.size())
        return _words.at((uint8_t)word);
    return 0;
}

void ControlCommandSr::setNumber(const ControlCommands &number)
{
    _number = number;
}

QByteArray ControlCommandSr::serialize()
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out.setByteOrder(QDataStream::LittleEndian);

    out << (uint16_t)_number;

    foreach (uint16_t var, _words) {
        out << var;
    }
    _words.clear();
    return array;
}

void ControlCommandSr::unserialize(StructControlCommand& header)
{
    _number = header.numberCC;
    _words.clear();

    switch (_number)
    {
    case ControlCommands::COMMAND_1007 :
    case ControlCommands::COMMAND_1009 :
    case ControlCommands::COMMAND_1010 :
    case ControlCommands::COMMAND_1013 :
    case ControlCommands::COMMAND_1014 :
    case ControlCommands::COMMAND_1015 :
    case ControlCommands::COMMAND_1023 :
    case ControlCommands::COMMAND_1024 :
    case ControlCommands::COMMAND_1029 :
    case ControlCommands::COMMAND_1031 :
    {
        _words.append(header.words[0]);
        break;
    }
    case ControlCommands::COMMAND_1019 :
    {
        _words.append(header.words[0]);
        _words.append(header.words[1]);
        _words.append(header.words[2]);
        _words.append(header.words[3]);
        break;
    }
    default:
        break;
    }
}
