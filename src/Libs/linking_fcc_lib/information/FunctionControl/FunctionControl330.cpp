#include "linkingFcc/infornation/FunctionControl/FunctionControl330.h"
#include "utils/ValueToByteArray.h"

static quint64 UnixTime_to_DelphiTDateTime(quint64 time)
{
    static const double UnixStartDate = 25569.0; // 01/01/1970
    static const int UTCshift = 10800;

    double delphiTime = (((double)time + UTCshift) / 86400.0) + UnixStartDate;

    quint64 res = 0;
    memcpy(&res, &delphiTime, sizeof(quint64));

    return res;
}

static int octalToDecimal(int num) {
    int temp = num;
    int val = 0;
    int base = 1;
    int count = temp;
    while (count) {
        int digit = count % 10;
        count = count / 10;
        val += digit * base;
        base = base * 8;
    }
    return val;
}

FunctionControl330::FunctionControl330(StructFunctionControl *control)
    : BaseFunctionControl(control)
{

}

void FunctionControl330::createByteArray(QByteArray &array)
{
    array.clear();

    uint16_t numberOTC = getRefInfoControl()->getNumberTicketedOTC();
    if(numberOTC < 6000)
        numberOTC = octalToDecimal(numberOTC);

    uint16_t idSI = (getRefInfoControl()->getIdSI());

    array.append(functions::toByteArrayLE<uint64_t>(UnixTime_to_DelphiTDateTime(getRefInfoControl()->getCurrentTime())));
    array.append(functions::toByteArrayLE<uint64_t>(UnixTime_to_DelphiTDateTime(getRefInfoControl()->getDigitizationTime())));
    array.append(functions::toByteArrayLE<int32_t>(getRefInfoControl()->getOffsetTime()));

    // word 11

    bool radyControl = getRefInfoControl()->getSystemState((uint8_t)SystemState::READY_ES);
    int16_t dp = getRefInfoControl()->getDopplerFreqPrediction();
    uint8_t mshu = getRefInfoControl()->getSystemState((uint8_t)SystemState::COMPLECT_MSHU);
    uint8_t ant = getRefInfoControl()->getSystemState((uint8_t)SystemState::TRANSMITTER);
    uint8_t um1 = getRefInfoControl()->getSystemState((uint8_t)SystemState::RADIATION_AMPLIFIER_1);
    uint8_t um2 = getRefInfoControl()->getSystemState((uint8_t)SystemState::RADIATION_AMPLIFIER_2);
    uint8_t modeWork = getRefInfoControl()->getSystemState((uint8_t)SystemState::MODE_WORK);
    uint8_t modePrep = getRefInfoControl()->getSystemState((uint8_t)SystemState::MODE_PREPARE);
    uint8_t modeIV = getRefInfoControl()->getSystemState((uint8_t)SystemState::MODE_IMIT_HF);
    uint8_t modeIF = getRefInfoControl()->getSystemState((uint8_t)SystemState::MODE_IMIT_IF);
    uint8_t liu = getRefInfoControl()->getSystemState((uint8_t)SystemState::MODE_CLOSE);
    uint8_t psh = !getRefInfoControl()->getSystemState((uint8_t)SystemState::LOCK_PNS);
    uint8_t carrier = getRefInfoControl()->getSystemState((uint8_t)SystemState::LOCK_CARRIER);
    uint8_t modemCompl = getRefInfoControl()->getComplects((uint8_t)Complects::MODEM);
    uint8_t tb1ready = getRefInfoControl()->getSwap((uint8_t)Swap::MODEM_COMPLECT_1);
    uint8_t tb2ready = getRefInfoControl()->getSwap((uint8_t)Swap::MODEM_COMPLECT_2);
    uint8_t um1alarm = getRefInfoControl()->getAlarmDevice(AlarmDevices::AMPLIFIER1);
    uint8_t um2alarm = getRefInfoControl()->getAlarmDevice(AlarmDevices::AMPLIFIER2);
    uint8_t umcompl = getRefInfoControl()->getComplects((uint8_t)Complects::AMPLIFIER);
;
    uint16_t word11 = 0;
    word11 |= (modePrep<< 13);
    word11 |=  (1 << 12);
    word11 |= (ant << 11);
    word11 |= (psh << 10);
    word11 |= (modemCompl << 9);
    word11 |= (radyControl << 8); // if we has control
    word11 |= ((tb1ready || tb2ready) << 7);
    word11 |= (modeIV << 6);
    word11 |=  (1 << 5);
    word11 |= (modeIF << 4);
    word11 |= (liu << 3);
    word11 |= (modeWork << 2);
    word11 |= ((um1 || um2) << 1);
    word11 |= (carrier);

    array.append(functions::toByteArrayLE<uint16_t>(word11));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getLiter()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getBandReceiver()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getSearchCorrection()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getDoplerCorrection()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getLiterPNS()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getLiterOTC()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getDecoder()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getSignalPower()));

    uint16_t word20 = 0;
    word20 |= ((um1alarm || um2alarm) << 12);
    word20 |= (getRefInfoControl()->getAlarmDevice(AlarmDevices::ANT)) << 11;
    word20 |= (!getRefInfoControl()->getAlarmDevice(AlarmDevices::ANT)) << 10;
    word20 |= ((umcompl == 1) << 9);
    word20 |= (getRefInfoControl()->getSwap((uint8_t)Swap::NP) << 7);
    word20 |= (getRefInfoControl()->getComplects((uint8_t)Complects::MSHY)) << 5;
    word20 |= (getRefInfoControl()->getComplects((uint8_t)Complects::MSHY2)) << 4;
    word20 |= ((getRefInfoControl()->getComplects((uint8_t)Complects::MSHY)) << 3);
    word20 |= ((modemCompl == 1) << 2);
    word20 |= ((getRefInfoControl()->getComplects((uint8_t)Complects::CONVERTER_UP) == 1));

    array.append(functions::toByteArrayLE<uint16_t>(word20));

    uint16_t word21 = 0;
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::AMPLIFIER1)) << 11);
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::AMPLIFIER2)) << 10);
    word21 |= (getRefInfoControl()->getSwap((uint8_t)Swap::ANT) << 9);
    word21 |= (1 << 8);
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::NP)) << 7);
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::TEST_TRANSLATION)) << 6);
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::MODEM_COMPLECT_1)) << 5);
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::MODEM_COMPLECT_2)) << 4);
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::CONVERTER_DOWN_COMPLECT_1)) << 3);
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::CONVERTER_DOWN_COMPLECT_2)) << 2);
    word21 |= ((getRefInfoControl()->getSwap((uint8_t)Swap::CONVERTER_UP_COMPLECT_2)) << 1);
    word21 |= (((getRefInfoControl()->getSwap((uint8_t)Swap::CONVERTER_UP_COMPLECT_1))));

    array.append(functions::toByteArrayLE<uint16_t>(word21));

    uint16_t word22 = 0;
    word22 |= getRefInfoControl()->getSwap((uint8_t)Swap::ANT) << 11;
    word22 |= getRefInfoControl()->getModeANT((uint8_t)ModeANT::TD) << 8;
    word22 |= getRefInfoControl()->getModeANT((uint8_t)ModeANT::CORRECTION) << 7;
    word22 |= (getRefInfoControl()->getModeORM((uint8_t)ModeORM::CHANGE_ANGLE) << 5 );
    word22 |= (getRefInfoControl()->getModeORM((uint8_t)ModeORM::CHANGE_ANGLE) << 3 );
    word22 |= (getRefInfoControl()->getModeANT((uint8_t)ModeANT::PROGRAMM) == 1) << 1;
    word22 |= (getRefInfoControl()->getModeANT((uint8_t)ModeANT::CORRECTION));

    array.append(functions::toByteArrayLE<uint16_t>(word22));
    array.append(functions::toByteArrayLE<int32_t>(getRefInfoControl()->getAzimuthFBS() * 60 * 6));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getElevationFBS() * 60 * 6));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getCorrectionAzimuth() * 60 * 6));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getCorrectionElevation() * 60 * 6));
    array.append(functions::toByteArrayLE<int32_t>(getRefInfoControl()->getPointAzimuth() * 60 * 6));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getPointElevation() * 60 * 6));

    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getWord33())); //presure
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getTemp())); //temperature
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getHumidity())); //humidity
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getWindDirection())); //winddir
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getWindSpeed())); //windpower

    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getTicketOTC()));
    array.append(functions::toByteArrayLE<uint16_t>(numberOTC));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getTicketSI()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getNumberTicketedSI()));
    array.append(functions::toByteArrayLE<uint16_t>(idSI));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getModeTLM()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getCounterTLM()));

    uint8_t word43 = 0;
    bool isRKO = (getRefInfoControl()->getModeORM((uint8_t)ModeORM::CHANGE_ANGLE) || getRefInfoControl()->getModeORM((uint8_t)ModeORM::CHANGE_DISTANCE));
    word43 |= ((getRefInfoControl()->getModeORM((uint8_t)ModeORM::SEC_1) == true) << 7);
    if(getRefInfoControl()->getModeORM((uint8_t)ModeORM::SEC_10) ||getRefInfoControl()->getModeORM((uint8_t)ModeORM::SEC_20))
        word43 |= ((getRefInfoControl()->getModeORM((uint8_t)ModeORM::SEC_10) ? 0 : 1) << 5);
    word43 |= (getRefInfoControl()->getModeANT((uint8_t)ModeANT::TD) && isRKO) << 3;
    word43 |= (getRefInfoControl()->getModeORM((uint8_t)ModeORM::CHANGE_ANGLE)) << 2;
    word43 |= isRKO  << 1;

    array.append(functions::toByteArrayLE<uint16_t>(word43));

    // 44 RKO measurement counter, 2 bytes
    array.append(functions::toByteArrayLE<quint16>(getRefInfoControl()->getCounterDistance()));

    // 45 angles measurement counter, 2 bytes
    array.append(functions::toByteArrayLE<quint16>(getRefInfoControl()->getCounterAngle()));

    // 46 frequency deviation, 2 bytes, low cost = 10Gz
    array.append(functions::toByteArrayLE<qint16>(getRefInfoControl()->getFrequencyDeviation() / 10));

    // 47 amplifier power (Watts), 2 bytes
    array.append(functions::toByteArrayLE<quint16>(getRefInfoControl()->getPowerReceiver()));

    // 48 amplifier temperate (C), 2 bytes
    array.append(functions::toByteArrayLE<quint16>(getRefInfoControl()->getTempReceiver()));

    // 49 amplifier attenuation, 2 bytes, low cost = 0.1dB
    array.append(functions::toByteArrayLE<quint16>(getRefInfoControl()->getAttenuator()));
}

bool FunctionControl330::getSystemState(const SystemState index)
{
    if(SYSTEM_STATE_MAP_330.values().contains(index))
        return getRefInfoControl()->getSystemState(SYSTEM_STATE_MAP_330.key(index));

    return false;
}

void FunctionControl330::setSystemState(const SystemState mode, const bool state)
{
    if(SYSTEM_STATE_MAP_330.values().contains(mode))
        getRefInfoControl()->setSystemState(SYSTEM_STATE_MAP_330.key(mode), state);
}

uint8_t FunctionControl330::getComplects(const Complects index)
{
    if(COMPLECTS_MAP_330.values().contains(index))
        return getRefInfoControl()->getComplects(COMPLECTS_MAP_330.key(index));

    return 0;
}

void FunctionControl330::setComplects(const Complects complect, const bool state)
{
    if(COMPLECTS_MAP_330.values().contains(complect))
        getRefInfoControl()->setComplects(COMPLECTS_MAP_330.key(complect), state);
}

bool FunctionControl330::getSwap(const Swap index)
{
    if(SWAP_MAP_330.values().contains(index))
        return getRefInfoControl()->getSwap(SWAP_MAP_330.key(index));

    return false;
}

void FunctionControl330::setSwap(const Swap numSwap, const bool state)
{
    if(SWAP_MAP_330.values().contains(numSwap))
        getRefInfoControl()->setSwap(SWAP_MAP_330.key(numSwap), state);
}

bool FunctionControl330::getModeANT(const ModeANT mode)
{
    if(MODE_ANT_MAP_330.values().contains(mode))
        return getRefInfoControl()->getModeANT(MODE_ANT_MAP_330.key(mode));

    return false;
}

void FunctionControl330::setModeANT(const ModeANT mode, const bool state)
{
    if(MODE_ANT_MAP_330.values().contains(mode))
        getRefInfoControl()->setModeANT(MODE_ANT_MAP_330.key(mode), state);
}

bool FunctionControl330::getModeORM(const ModeORM mode)
{
    if(MODE_ORM_MAP_330.values().contains(mode))
        return getRefInfoControl()->getModeORM(MODE_ORM_MAP_330.key(mode));

    return false;
}

void FunctionControl330::setModeORM(const ModeORM mode, const bool state)
{
    if(MODE_ORM_MAP_330.values().contains(mode))
        getRefInfoControl()->setModeORM(MODE_ORM_MAP_330.key(mode), state);
}

void FunctionControl330::resetTempMeasurementORM()
{

}

void FunctionControl330::setParamsPreviousCMS(OldParamsCMS &strct)
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
    setSwap(Swap::SCU1, strct.SCU1);
    setSwap(Swap::SCU2, strct.SCU2);

    setModeANT(ModeANT::MANUAL, strct.MANUAL);
    setModeANT(ModeANT::PROGRAMM, strct.PROGRAMM);
    setModeANT(ModeANT::CORRECTION, strct.CORRECTION);
    setModeANT(ModeANT::TD, strct.TD);
    setModeANT(ModeANT::CALIBRATION, strct.CALIBRATION);

    setModeORM(ModeORM::CHANGE_DISTANCE, strct.CHANGE_DISTANCE);
    setModeORM(ModeORM::CHANGE_ANGLE, strct.CHANGE_ANGLE);
    setModeORM(ModeORM::ID_ORM, strct.ID_ORM);
}
