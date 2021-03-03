#include "linkingFcc/infornation/CommandControl/FactoryCommandControl.h"

FactoryCommandControl::FactoryCommandControl(const int16_t ka)
{
    switch (ka)
    {

    case 649:
    {
        _command = QSharedPointer<CommandControl649>(new CommandControl649());
        break;
    }

    default:
    {
        _command = QSharedPointer<CommandControl>(new CommandControl());
        break;
    }

    }
}

QSharedPointer<BaseCommandControl> FactoryCommandControl::getCommandControl()
{
    return _command;
}
