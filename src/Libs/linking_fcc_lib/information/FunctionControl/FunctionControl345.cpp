#include "linkingFcc/infornation/FunctionControl/FunctionControl345.h"

FunctionControl345::FunctionControl345(StructFunctionControl* control)
    : BaseFunctionControl(control)
{

}

void FunctionControl345::createByteArray(QByteArray &array)
{
    createBaseByteArray(array);
}

bool FunctionControl345::getSystemState(const SystemState index)
{
    if(SYSTEM_STATE_MAP_345.values().contains(index))
        return getRefInfoControl()->getSystemState(SYSTEM_STATE_MAP_345.key(index));

    return false;
}

void FunctionControl345::setSystemState(const SystemState mode, const bool state)
{
    if(SYSTEM_STATE_MAP_345.values().contains(mode))
        getRefInfoControl()->setSystemState(SYSTEM_STATE_MAP_345.key(mode), state);
}

uint8_t FunctionControl345::getComplects(const Complects index)
{
    if(COMPLECTS_MAP_345.values().contains(index))
        return getRefInfoControl()->getComplects(COMPLECTS_MAP_345.key(index));

    return 0;
}

void FunctionControl345::setComplects(const Complects complect, const bool state)
{
    if(COMPLECTS_MAP_345.values().contains(complect))
        getRefInfoControl()->setComplects(COMPLECTS_MAP_345.key(complect), state);
}

bool FunctionControl345::getSwap(const Swap index)
{
    if(SWAP_MAP_345.values().contains(index))
        return getRefInfoControl()->getSwap(SWAP_MAP_345.key(index));

    return false;
}

void FunctionControl345::setSwap(const Swap numSwap, const bool state)
{
    if(SWAP_MAP_345.values().contains(numSwap))
        getRefInfoControl()->setSwap(SWAP_MAP_345.key(numSwap), state);
}

bool FunctionControl345::getModeANT(const ModeANT mode)
{
    if(MODE_ANT_MAP_345.values().contains(mode))
        return getRefInfoControl()->getModeANT(MODE_ANT_MAP_345.key(mode));

    return false;
}

void FunctionControl345::setModeANT(const ModeANT mode, const bool state)
{
    if(MODE_ANT_MAP_345.values().contains(mode))
        getRefInfoControl()->setModeANT(MODE_ANT_MAP_345.key(mode), state);
}

bool FunctionControl345::getModeORM(const ModeORM mode)
{
    if(MODE_ORM_MAP_345.values().contains(mode))
        return getRefInfoControl()->getModeORM(MODE_ORM_MAP_345.key(mode));

    return false;
}

void FunctionControl345::setModeORM(const ModeORM mode, const bool state)
{
    if(MODE_ORM_MAP_345.values().contains(mode))
        getRefInfoControl()->setModeORM(MODE_ORM_MAP_345.key(mode), state);
}

void FunctionControl345::resetTempMeasurementORM()
{

}

void FunctionControl345::setParamsPreviousCMS(OldParamsCMS &strct)
{

}
