#include "linkingFcc/infornation/FunctionControl/FunctionControl346.h"

FunctionControl346::FunctionControl346(StructFunctionControl* control)
    : BaseFunctionControl(control)
{

}

void FunctionControl346::createByteArray(QByteArray &array)
{
    createBaseByteArray(array);
}

bool FunctionControl346::getSystemState(const SystemState index)
{
    if(SYSTEM_STATE_MAP_346.values().contains(index))
        return getRefInfoControl()->getSystemState(SYSTEM_STATE_MAP_346.key(index));

    return false;
}

void FunctionControl346::setSystemState(const SystemState mode, const bool state)
{
    if(SYSTEM_STATE_MAP_346.values().contains(mode))
        getRefInfoControl()->setSystemState(SYSTEM_STATE_MAP_346.key(mode), state);
}

uint8_t FunctionControl346::getComplects(const Complects index)
{
    if(COMPLECTS_MAP_346.values().contains(index))
        return getRefInfoControl()->getComplects(COMPLECTS_MAP_346.key(index));

    return 0;
}

void FunctionControl346::setComplects(const Complects complect, const bool state)
{
    if(COMPLECTS_MAP_346.values().contains(complect))
        getRefInfoControl()->setComplects(COMPLECTS_MAP_346.key(complect), state);
}

bool FunctionControl346::getSwap(const Swap index)
{
    if(SWAP_MAP_346.values().contains(index))
        return getRefInfoControl()->getSwap(SWAP_MAP_346.key(index));

    return false;
}

void FunctionControl346::setSwap(const Swap numSwap, const bool state)
{
    if(SWAP_MAP_346.values().contains(numSwap))
        getRefInfoControl()->setSwap(SWAP_MAP_346.key(numSwap), state);
}

bool FunctionControl346::getModeANT(const ModeANT mode)
{
    if(MODE_ANT_MAP_346.values().contains(mode))
        return getRefInfoControl()->getModeANT(MODE_ANT_MAP_346.key(mode));

    return false;
}

void FunctionControl346::setModeANT(const ModeANT mode, const bool state)
{
    if(MODE_ANT_MAP_346.values().contains(mode))
        getRefInfoControl()->setModeANT(MODE_ANT_MAP_346.key(mode), state);
}

bool FunctionControl346::getModeORM(const ModeORM mode)
{
    if(MODE_ORM_MAP_346.values().contains(mode))
        return getRefInfoControl()->getModeORM(MODE_ORM_MAP_346.key(mode));

    return false;
}

void FunctionControl346::setModeORM(const ModeORM mode, const bool state)
{
    if(MODE_ORM_MAP_346.values().contains(mode))
        getRefInfoControl()->setModeORM(MODE_ORM_MAP_346.key(mode), state);
}

void FunctionControl346::resetTempMeasurementORM()
{

}

void FunctionControl346::setParamsPreviousCMS(OldParamsCMS &strct)
{

}
