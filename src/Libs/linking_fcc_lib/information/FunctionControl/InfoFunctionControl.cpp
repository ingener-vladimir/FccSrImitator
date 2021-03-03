#include "linkingFcc/infornation/FunctionControl/InfoFunctionControl.h"
#include "utils/ValueToByteArray.h"

#include <QDateTime>
#include <QFile>

#include <iostream>
#include <bitset>

//void InfoFunctionControl::createByteArray_649(QByteArray &array)
//{
//    array.clear();

//    //1-4
//    array.append(toByteArrayLE<uint64_t>(UnixTime_to_DelphiTDateTime(getCurrentTime())));
//    //5-8
//    array.append(toByteArrayLE<uint64_t>(UnixTime_to_DelphiTDateTime(getDigitizationTime())));
//    //9-10
//    array.append(toByteArrayLE<int32_t>(getOffsetTime()));
//    //11

//    quint16 word11 = 0;
//    word11 |= (1 << 14);
//    word11 |= ((getSystemState(SystemState::MODE_PREPARE)) << 13);
//    word11 |=  (1 << 12);
//    word11 |= (getSystemState(SystemState::TRANSMITTER) << 11);
//    word11 |= (getSystemState(SystemState::MODULATION_PNS) << 10);
//    word11 |= ((getComplects(Complects::MODEM) == 2) << 9);
//    word11 |= (getSystemState(SystemState::READY_ES) << 8); // if we has control
//    word11 |= ((getSwap(Swap::MODEM_COMPLECT_1) || getSwap(Swap::MODEM_COMPLECT_2)) << 7);
//    word11 |= ((getSystemState(SystemState::MODE_IMIT_HF)) << 6);
//    word11 |=  (1 << 5);
//    word11 |= (getSystemState(SystemState::MODE_IMIT_IF) << 4);
//    word11 |= (getSystemState(SystemState::MODE_CLOSE) << 3);
//    word11 |= ((getSystemState(SystemState::MODE_WORK)) << 2);
//    word11 |= ((getSystemState(SystemState::RADIATION_AMPLIFIER_1) || getSystemState(SystemState::RADIATION_AMPLIFIER_2)) << 1);
//    word11 |= (getSystemState(SystemState::LOCK_CARRIER));
//    array.append(toByteArrayLE<uint16_t>(word11));
//    //12
//    array.append(toByteArrayLE<uint16_t>(getLiter()));
//    //13
//    array.append(toByteArrayLE<uint16_t>(getBandReceiver()));
//    //14
//    array.append(toByteArrayLE<int16_t>(getSearchCorrection()));
//    //15
//    array.append(toByteArrayLE<int16_t>(getDoplerCorrection()));
//    //16
//    array.append(toByteArrayLE<uint16_t>(getLiterPNS()));
//    //17
//    array.append(toByteArrayLE<uint16_t>(getLiterOTC()));
//    //18
//    array.append(toByteArrayLE<uint16_t>(getDecoder()));
//    //19
//    array.append(toByteArrayLE<int16_t>(getSignalPower()));
//    //20
//    quint16 word20 = 0;
//    bool umAlarm = getAlarmDevice(AlarmDevices::AMPLIFIER1) || getAlarmDevice(AlarmDevices::AMPLIFIER2);
//    word20 |= ((getComplects(Complects::POLAR_UP) == 1) << 14); // up
//    word20 |= ((getComplects(Complects::POLAR_RECEIVER) == 1) << 15); // down
//    word20 |= (umAlarm << 12);
//    word20 |= (getSystemState(SystemState::TRANSMITTER)) << 11;
//    word20 |= (!getSystemState(SystemState::TRANSMITTER)) << 10;
//    //word20 |= ((dc->komplUm() == 2) << 9);
//    word20 |= (1 << 7);
//    //word20 |= (dc->vkp1Switch()) << 5;
//    //word20 |= (dc->vkp2Switch()) << 4;
//    word20 |= ((getComplects(Complects::CONVERTER_UP) == 2) << 3);
//    //word20 |= ((tbCompl == 2) << 2);
//    //word20 |= (dc->yauReady());
//    array.append(toByteArrayLE<uint16_t>(word20));

//    //21 ?????
//    array.append(toByteArrayLE<uint16_t>(getSwap()));
//    array.append(toByteArrayLE<uint16_t>(getModeANT()));
//    array.append(toByteArrayLE<int32_t>(getAzimuthFBS() * 60 * 6));
//    array.append(toByteArrayLE<int16_t>(getElevationFBS() * 60 * 6));
//    array.append(toByteArrayLE<int16_t>(getCorrectionAzimuth() * 60 * 6));
//    array.append(toByteArrayLE<int16_t>(getCorrectionElevation() * 60 * 6));
//    array.append(toByteArrayLE<int32_t>(getPointAzimuth() * 60 * 6));
//    array.append(toByteArrayLE<int16_t>(getPointElevation() * 60 * 6));
//    array.append(toByteArrayLE<uint16_t>(getKeySCPI()));
//    array.append(toByteArrayLE<uint16_t>(getKeyOSK()));
//    array.append(toByteArrayLE<uint16_t>(getReserve1()));
//    array.append(toByteArrayLE<uint16_t>(getReserve2()));
//    array.append(toByteArrayLE<uint16_t>(getReserve3()));
//    array.append(toByteArrayLE<uint16_t>(getTicketOTC()));
//    array.append(toByteArrayLE<uint16_t>(getNumberTicketedOTC()));
//    array.append(toByteArrayLE<uint16_t>(getTicketSI()));
//    array.append(toByteArrayLE<uint16_t>(getNumberTicketedSI()));
//    array.append(toByteArrayLE<uint16_t>(getIdSI()));
//    array.append(toByteArrayLE<uint16_t>(getModeTLM()));
//    array.append(toByteArrayLE<uint16_t>(getCounterTLM()));
//    array.append(toByteArrayLE<uint16_t>(getModeORM()));
//    array.append(toByteArrayLE<uint8_t>(getCounterDistance()));
//    array.append(toByteArrayLE<uint8_t>(getCounterAngle()));
//    array.append(toByteArrayLE<int16_t>(getDopplerFreqPrediction()));
//    array.append(toByteArrayLE<int16_t>(getFrequencyDeviation()));
//    array.append(toByteArrayLE<uint16_t>(getAlarmDevice()));
//    array.append(toByteArrayLE<uint16_t>(getPowerReceiver()));
//    array.append(toByteArrayLE<uint8_t>(getAttenuator()));
//    array.append(toByteArrayLE<int8_t>(getTempReceiver()));
//}

InfoFunctionControl::InfoFunctionControl(StructFunctionControl* control)
    : BaseFunctionControl(control)
{

}

void InfoFunctionControl::createByteArray(QByteArray &array)
{
    createBaseByteArray(array);

    array.append(functions::toByteArrayLE<uint8_t>(static_cast<uint8_t>(getRefInfoControl()->getCounterDistance())));
    array.append(functions::toByteArrayLE<uint8_t>(static_cast<uint8_t>(getRefInfoControl()->getCounterAngle())));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getDopplerFreqPrediction()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getFrequencyDeviation()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getAlarmDevice()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getPowerReceiver()));
    array.append(functions::toByteArrayLE<int8_t>(static_cast<int8_t>(getRefInfoControl()->getTempReceiver())));
    array.append(functions::toByteArrayLE<uint8_t>(static_cast<uint8_t>(getRefInfoControl()->getAttenuator())));

    /*static QFile ifctFile("./IFCT.txt");
    if(!ifctFile.isOpen()) {
        ifctFile.open(QIODevice::WriteOnly);
    }

    QDateTime time = QDateTime::currentDateTime();

    std::string sWord36 = std::bitset<16>(getTicketOTC()).to_string();
    std::string sWord37 = std::bitset<16>(numberOTC).to_string();
    std::string sWord38 = std::bitset<16>(getTicketSI()).to_string();
    std::string sWord39 = std::bitset<16>(getNumberTicketedSI()).to_string();
    std::string sWord40 = std::bitset<16>(idSI).to_string();

    QString line = QString("T: %1 QRK:%2 NRK:%3 QSI:%4 NSI:%5 ISI:%6\n").arg(time.toString()).arg(sWord36.c_str()).arg(sWord37.c_str()).arg(sWord38.c_str()).arg(sWord39.c_str()).arg(sWord40.c_str());

    ifctFile.write(line.toStdString().c_str(), line.toStdString().size());
    ifctFile.flush();*/
}

bool InfoFunctionControl::getSystemState(const SystemState index)
{
    if(SYSTEM_STATE_MAP.values().contains(index))
        return getRefInfoControl()->getSystemState(SYSTEM_STATE_MAP.key(index));

    return false;
}

void InfoFunctionControl::setSystemState(const SystemState mode, const bool state)
{
    if(SYSTEM_STATE_MAP.values().contains(mode))
        getRefInfoControl()->setSystemState(SYSTEM_STATE_MAP.key(mode), state);
}

uint8_t InfoFunctionControl::getComplects(const Complects index)
{
    if(COMPLECTS_MAP.values().contains(index))
        return getRefInfoControl()->getComplects(COMPLECTS_MAP.key(index));

    return 0;
}

void InfoFunctionControl::setComplects(const Complects complect, const bool state)
{
    if(COMPLECTS_MAP.values().contains(complect))
        getRefInfoControl()->setComplects(COMPLECTS_MAP.key(complect), state);
}

bool InfoFunctionControl::getSwap(const Swap index)
{
    if(SWAP_MAP.values().contains(index))
        return getRefInfoControl()->getSwap(SWAP_MAP.key(index));

    return 0;
}

void InfoFunctionControl::setSwap(const Swap numSwap, const bool state)
{
    if(SWAP_MAP.values().contains(numSwap))
        getRefInfoControl()->setSwap(SWAP_MAP.key(numSwap), state);
}

bool InfoFunctionControl::getModeANT(const ModeANT mode)
{
    if(MODE_ANT_MAP.values().contains(mode))
        return getRefInfoControl()->getModeANT(MODE_ANT_MAP.key(mode));

    return false;
}

void InfoFunctionControl::setModeANT(const ModeANT mode, const bool state)
{
    if(MODE_ANT_MAP.values().contains(mode))
        getRefInfoControl()->setModeANT(MODE_ANT_MAP.key(mode), state);
}

bool InfoFunctionControl::getModeORM(const ModeORM mode)
{
    if(MODE_ORM_MAP.values().contains(mode))
        return getRefInfoControl()->getModeORM(MODE_ORM_MAP.key(mode));

    return false;
}

void InfoFunctionControl::setModeORM(const ModeORM mode, const bool state)
{
    if(MODE_ORM_MAP.values().contains(mode))
        getRefInfoControl()->setModeORM(MODE_ORM_MAP.key(mode), state);
}

void InfoFunctionControl::resetTempMeasurementORM()
{
    setModeORM(ModeORM::SEC_1, false);
    setModeORM(ModeORM::SEC_10, false);
    setModeORM(ModeORM::SEC_20, false);
}

void InfoFunctionControl::setParamsPreviousCMS(OldParamsCMS &strct)
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
