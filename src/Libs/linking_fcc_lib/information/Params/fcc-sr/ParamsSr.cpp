#include "linkingFcc/infornation/Params/fcc-sr/ParamsSr.h"

ParamsSr::ParamsSr()
{

}

Telemetry &ParamsSr::getTelemetry()
{
    return telemetry;
}

FunctionControlSr &ParamsSr::getFunctionControlSr()
{
    return functionControlSr;
}

SingleCommandSr &ParamsSr::getSingleCommandSr()
{
    return singleCommandSr;
}

ControlCommandSr &ParamsSr::getControlCommandSr()
{
    return controlCommandSr;
}

PropagationSignalDelay& ParamsSr::getPropagationSignalDelay()
{
    return propagationSignalDelay;
}

DoplerFrequencyOffset& ParamsSr::getDoplerFrequencyOffset()
{
    return doplerFrequencyOffset;
}

SpecialInformationSr& ParamsSr::getSpecialInformationSr()
{
    return specialInformationSr;
}
