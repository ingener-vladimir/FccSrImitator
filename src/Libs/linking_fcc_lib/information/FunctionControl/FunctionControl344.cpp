#include "linkingFcc/infornation/FunctionControl/FunctionControl344.h"

FunctionControl344::FunctionControl344(StructFunctionControl *control)
    : BaseFunctionControl(control)
{

}

void FunctionControl344::createByteArray(QByteArray &array)
{
    createBaseByteArray(array);
}

bool FunctionControl344::getSystemState(const SystemState index)
{
    if(SYSTEM_STATE_MAP_344.values().contains(index))
        return getRefInfoControl()->getSystemState(SYSTEM_STATE_MAP_344.key(index));

    return false;
}

void FunctionControl344::setSystemState(const SystemState mode, const bool state)
{
    if(SYSTEM_STATE_MAP_344.values().contains(mode))
        getRefInfoControl()->setSystemState(SYSTEM_STATE_MAP_344.key(mode), state);
}

uint8_t FunctionControl344::getComplects(const Complects index)
{
    if(COMPLECTS_MAP_344.values().contains(index))
        return getRefInfoControl()->getComplects(COMPLECTS_MAP_344.key(index));

    return 0;
}

void FunctionControl344::setComplects(const Complects complect, const bool state)
{
    if(COMPLECTS_MAP_344.values().contains(complect))
        getRefInfoControl()->setComplects(COMPLECTS_MAP_344.key(complect), state);
}

bool FunctionControl344::getSwap(const Swap index)
{
    if(SWAP_MAP_344.values().contains(index))
        return getRefInfoControl()->getSwap(SWAP_MAP_344.key(index));

    return false;
}

void FunctionControl344::setSwap(const Swap numSwap, const bool state)
{
    if(SWAP_MAP_344.values().contains(numSwap))
        getRefInfoControl()->setSwap(SWAP_MAP_344.key(numSwap), state);
}

bool FunctionControl344::getModeANT(const ModeANT mode)
{
    if(MODE_ANT_MAP_344.values().contains(mode))
        return getRefInfoControl()->getModeANT(MODE_ANT_MAP_344.key(mode));

    return false;
}

void FunctionControl344::setModeANT(const ModeANT mode, const bool state)
{
    if(MODE_ANT_MAP_344.values().contains(mode))
        getRefInfoControl()->setModeANT(MODE_ANT_MAP_344.key(mode), state);
}

bool FunctionControl344::getModeORM(const ModeORM mode)
{
    if(MODE_ORM_MAP_344.values().contains(mode))
        return getRefInfoControl()->getModeORM(MODE_ORM_MAP_344.key(mode));

    return false;
}

void FunctionControl344::setModeORM(const ModeORM mode, const bool state)
{
    if(MODE_ORM_MAP_344.values().contains(mode))
        getRefInfoControl()->setModeORM(MODE_ORM_MAP_344.key(mode), state);
}

void FunctionControl344::resetTempMeasurementORM()
{

}

void FunctionControl344::setParamsPreviousCMS(OldParamsCMS &strct)
{

}
