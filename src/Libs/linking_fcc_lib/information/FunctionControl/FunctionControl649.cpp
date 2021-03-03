#include "linkingFcc/infornation/FunctionControl/FunctionControl649.h"
#include "utils/ValueToByteArray.h"

FunctionControl649::FunctionControl649(StructFunctionControl *control)
    : BaseFunctionControl(control)
{

}

bool FunctionControl649::getSystemState(const SystemState index)
{
    if(SYSTEM_STATE_MAP_649.values().contains(index))
        return getRefInfoControl()->getSystemState(SYSTEM_STATE_MAP_649.key(index));

    return false;
}

void FunctionControl649::setSystemState(const SystemState mode, const bool state)
{
    if(SYSTEM_STATE_MAP_649.values().contains(mode))
        getRefInfoControl()->setSystemState(SYSTEM_STATE_MAP_649.key(mode), state);
}

uint8_t FunctionControl649::getComplects(const Complects index)
{
    if(COMPLECTS_MAP_649.values().contains(index))
        return getRefInfoControl()->getComplects(COMPLECTS_MAP_649.key(index));

    return 0;
}

void FunctionControl649::setComplects(const Complects complect, const bool state)
{
    if(COMPLECTS_MAP_649.values().contains(complect))
        getRefInfoControl()->setComplects(COMPLECTS_MAP_649.key(complect), state);
}

bool FunctionControl649::getSwap(const Swap index)
{
    if(SWAP_MAP_649.values().contains(index))
        return getRefInfoControl()->getSwap(SWAP_MAP_649.key(index));

    return 0;
}

void FunctionControl649::setSwap(const Swap numSwap, const bool state)
{
    if(SWAP_MAP_649.values().contains(numSwap))
        getRefInfoControl()->setSwap(SWAP_MAP_649.key(numSwap), state);
}

bool FunctionControl649::getModeANT(const ModeANT mode)
{
    if(MODE_ANT_MAP_649.values().contains(mode))
        return getRefInfoControl()->getModeANT(MODE_ANT_MAP_649.key(mode));

    return false;
}

void FunctionControl649::setModeANT(const ModeANT mode, const bool state)
{
    if(MODE_ANT_MAP_649.values().contains(mode))
        getRefInfoControl()->setModeANT(MODE_ANT_MAP_649.key(mode), state);
}

bool FunctionControl649::getModeORM(const ModeORM mode)
{
    if(MODE_ORM_MAP_649.values().contains(mode))
        return getRefInfoControl()->getModeORM(MODE_ORM_MAP_649.key(mode));

    return false;
}

void FunctionControl649::setModeORM(const ModeORM mode, const bool state)
{
    if(MODE_ORM_MAP_649.values().contains(mode))
        getRefInfoControl()->setModeORM(MODE_ORM_MAP_649.key(mode), state);
}

void FunctionControl649::createByteArray(QByteArray &array)
{
    createBaseByteArray(array);

    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getCounterDistance()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getCounterAngle()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getFrequencyDeviation()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getPowerReceiver()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getTempReceiver()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getAttenuator()));
}

void FunctionControl649::resetTempMeasurementORM()
{
    setModeORM(ModeORM::SEC_10_20, false);
}

void FunctionControl649::setParamsPreviousCMS(OldParamsCMS &strct)
{  
    setSystemState(SystemState::MODE_WORK, strct.MODE_WORK);
    setSystemState(SystemState::MODE_IMIT_IF, strct.MODE_IMIT_IF);
    setSystemState(SystemState::MODE_IMIT_HF, strct.MODE_IMIT_HF);
    setSystemState(SystemState::MODE_PREPARE, strct.MODE_PREPARE);
    setSystemState(SystemState::RADIATION_AMPLIFIER_1, strct.RADIATION_AMPLIFIER_1);
    setSystemState(SystemState::RADIATION_AMPLIFIER_2, strct.RADIATION_AMPLIFIER_2);
    setSystemState(SystemState::MODULATION_PNS, strct.MODULATION_PNS);

    setComplects(Complects::CONVERTER_UP, strct.CONVERTER_UP);
    setComplects(Complects::MSHY, strct.MSHY);
    setComplects(Complects::POLAR_UP, strct.POLAR_UP);

    setSwap(Swap::LIU, strct.LIU);
    setSwap(Swap::CONVERTER_UP_COMPLECT_1, strct.CONVERTER_UP_COMPLECT_1);
    setSwap(Swap::CONVERTER_DOWN_COMPLECT_2, strct.CONVERTER_DOWN_COMPLECT_2);
    setSwap(Swap::CONVERTER_DOWN_COMPLECT_1, strct.CONVERTER_DOWN_COMPLECT_1);
    setSwap(Swap::NP_2, strct.NP_2);
    setSwap(Swap::NP_1, strct.NP_1);
    setSwap(Swap::NP, strct.NP);
    setSwap(Swap::AYY495_COMPLECT_1, strct.AYY495_COMPLECT_1);
    setSwap(Swap::AYY495_COMPLECT_2, strct.AYY495_COMPLECT_2);
    setSwap(Swap::TEST_TRANSLATION, strct.TEST_TRANSLATION);
    setSwap(Swap::ANT, strct.ANT);

    setModeANT(ModeANT::MANUAL, strct.MANUAL);
    setModeANT(ModeANT::PROGRAMM, strct.PROGRAMM);
    setModeANT(ModeANT::CORRECTION, strct.CORRECTION);
    setModeANT(ModeANT::TD, strct.TD);
    setModeANT(ModeANT::CALIBRATION, strct.CALIBRATION);

    setModeORM(ModeORM::CHANGE_DISTANCE, strct.CHANGE_DISTANCE);
    setModeORM(ModeORM::CHANGE_ANGLE, strct.CHANGE_ANGLE);
    setModeORM(ModeORM::ID_ORM, strct.ID_ORM);
}

