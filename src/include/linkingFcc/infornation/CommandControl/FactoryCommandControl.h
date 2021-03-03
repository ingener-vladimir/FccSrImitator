#ifndef FACTORYCOMMANDCONTROL_H
#define FACTORYCOMMANDCONTROL_H

#include <QSharedPointer>

#include "CommandControl.h"
#include "CommandControl649.h"

class FactoryCommandControl
{
    QSharedPointer<BaseCommandControl> _command{nullptr};

public:
    FactoryCommandControl(const int16_t ka);

    QSharedPointer<BaseCommandControl> getCommandControl();
};

#endif // FACTORYCOMMANDCONTROL_H
