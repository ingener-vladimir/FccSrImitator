#include "linkingFcc/infornation/CommandControl/CommandControl649.h"

CommandControl649::~CommandControl649()
{

}

void CommandControl649::unserializeCommand(uint16_t nKA,
                                           HeaderControlCommand &header)
{
    _numKA = nKA;
    _numCommand = header.numberCC;

    switch(_numCommand)
    {

    case CommandsControl::COMMAND_4007 :
    case CommandsControl::COMMAND_4008 :
    case CommandsControl::COMMAND_4009 :
    case CommandsControl::COMMAND_4010 :
    case CommandsControl::COMMAND_4015 :
    case CommandsControl::COMMAND_4016 :
    case CommandsControl::COMMAND_4017 :
    case CommandsControl::COMMAND_4018 :
    case CommandsControl::COMMAND_4019 :
    case CommandsControl::COMMAND_4023 :
    case CommandsControl::COMMAND_4024 :
    case CommandsControl::COMMAND_4029 :
    case CommandsControl::COMMAND_4032 :
    case CommandsControl::COMMAND_4036 :
    case CommandsControl::COMMAND_4034 :
    case CommandsControl::COMMAND_4037 :
    case CommandsControl::COMMAND_4047 :
    case CommandsControl::COMMAND_4049 :
    case CommandsControl::COMMAND_4053 :
    {
        params.append(header.words[(int8_t)Words::WORD1]);
        break;
    }

    case CommandsControl::COMMAND_4031 :
    {
        params.append(header.words[(int8_t)Words::WORD1]);
        params.append(header.words[(int8_t)Words::WORD2]);
        break;
    }

    case CommandsControl::COMMAND_4020 :
    {
        params.append(header.words[(int8_t)Words::WORD1]);
        params.append(header.words[(uint8_t)Words::WORD2]);
        params.append(header.words[(int8_t)Words::WORD3]);
        params.append(header.words[(int8_t)Words::WORD4]);
        break;
    }

    default:
        break;
    }
}
