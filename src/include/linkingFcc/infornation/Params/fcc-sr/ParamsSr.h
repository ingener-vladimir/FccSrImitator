#ifndef PARAMSSR_H
#define PARAMSSR_H

#include "linkingFcc/Singleton/Singleton.h"
#include "linkingFcc/infornation/Telemetry/Telemetry.h"
#include "linkingFcc/infornation/FunctionControl/fcc-sr/FunctionControlSr.h"
#include "linkingFcc/infornation/SingleCommand/fcc_sr/SingleCommandSr.h"
#include "linkingFcc/infornation/CommandControl/fcc-sr/ControlCommandSr.h"
#include "linkingFcc/infornation/PropagationSignalDelay/PropagationSignalDelay.h"
#include "linkingFcc/infornation/DoplerFrequencyOffset/DoplerFrequencyOffset.h"
#include "linkingFcc/infornation/SpecialInformation/fcc-sr/SpecialInformationSr.h"

class ParamsSr
{
    Telemetry telemetry;
    FunctionControlSr functionControlSr;
    SingleCommandSr singleCommandSr;
    ControlCommandSr controlCommandSr;
    PropagationSignalDelay propagationSignalDelay;
    DoplerFrequencyOffset doplerFrequencyOffset;
    SpecialInformationSr specialInformationSr;
public:
    ParamsSr();

    Telemetry& getTelemetry();
    FunctionControlSr& getFunctionControlSr();
    SingleCommandSr& getSingleCommandSr();
    ControlCommandSr& getControlCommandSr();
    PropagationSignalDelay& getPropagationSignalDelay();
    DoplerFrequencyOffset& getDoplerFrequencyOffset();
    SpecialInformationSr& getSpecialInformationSr();
};

using ParamsSrSingleton = Singleton<ParamsSr>;

#endif // PARAMSSR_H
