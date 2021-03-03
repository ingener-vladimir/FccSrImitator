#include "linkingFcc/infornation/FunctionControl/BaseFunctionControl.h"
#include "utils/ValueToByteArray.h"

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

BaseFunctionControl::BaseFunctionControl(StructFunctionControl *infoControl)
{
    setInfoControl(infoControl);
}

BaseFunctionControl &BaseFunctionControl::operator=(BaseFunctionControl &control)
{
    if(this != &control)
        _infoControl = control.getRefInfoControl();

    return *this;
}

BaseFunctionControl::BaseFunctionControl(BaseFunctionControl &control)
{
    _infoControl = control.getRefInfoControl();
}

void BaseFunctionControl::createBaseByteArray(QByteArray &array)
{
    array.clear();

    uint16_t numberOTC = getRefInfoControl()->getNumberTicketedOTC();
    if(numberOTC < 6000)
        numberOTC = octalToDecimal(numberOTC);

    uint16_t idSI = (getRefInfoControl()->getIdSI());

    array.append(functions::toByteArrayLE<uint64_t>(getRefInfoControl()->getCurrentTime()));
    array.append(functions::toByteArrayLE<uint64_t>(getRefInfoControl()->getDigitizationTime()));
    array.append(functions::toByteArrayLE<int32_t>(getRefInfoControl()->getOffsetTime()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getValueSystemState()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getLiter()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getBandReceiver()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getSearchCorrection()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getDoplerCorrection()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getLiterPNS()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getLiterOTC()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getDecoder()));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getSignalPower()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getValueComplects()));
    uint16_t word21 = getRefInfoControl()->getValueSwap();
    word21 |= 1 << 11;
    array.append(functions::toByteArrayLE<uint16_t>(word21));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getValueModeANT()));
    array.append(functions::toByteArrayLE<int32_t>(getRefInfoControl()->getAzimuthFBS() * 60 * 6));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getElevationFBS() * 60 * 6));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getCorrectionAzimuth() * 60 * 6));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getCorrectionElevation() * 60 * 6));
    array.append(functions::toByteArrayLE<int32_t>(getRefInfoControl()->getPointAzimuth() * 60 * 6));
    array.append(functions::toByteArrayLE<int16_t>(getRefInfoControl()->getPointElevation() * 60 * 6));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getKeySCPI()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getKeyOSK()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getWord33()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getWord34()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getWord35()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getTicketOTC()));
    array.append(functions::toByteArrayLE<uint16_t>(numberOTC));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getTicketSI()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getNumberTicketedSI()));
    array.append(functions::toByteArrayLE<uint16_t>(idSI));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getModeTLM()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getCounterTLM()));
    array.append(functions::toByteArrayLE<uint16_t>(getRefInfoControl()->getValueModeORM()));
}

StructFunctionControl* BaseFunctionControl::getRefInfoControl()
{
    QMutexLocker lock(&_mutex);
    return _infoControl;
}

OldParamsCMS BaseFunctionControl::getOldParams()
{
    OldParamsCMS oldParams;

    oldParams.MODE_WORK = getSystemState(SystemState::MODE_WORK);
    oldParams.MODE_IMIT_IF = getSystemState(SystemState::MODE_IMIT_IF);
    oldParams.MODE_IMIT_HF = getSystemState(SystemState::MODE_IMIT_HF);
    oldParams.MODE_PREPARE = getSystemState(SystemState::MODE_PREPARE);
    oldParams.RADIATION_AMPLIFIER_1 = getSystemState(SystemState::RADIATION_AMPLIFIER_1);
    oldParams.RADIATION_AMPLIFIER_2 = getSystemState(SystemState::RADIATION_AMPLIFIER_2);
    oldParams.MODULATION_PNS = getSystemState(SystemState::MODULATION_PNS);

    oldParams.CONVERTER_UP = getComplects(Complects::CONVERTER_UP) == 2 ? true : false;
    oldParams.MSHY = getComplects(Complects::MSHY) == 2 ? true : false;
    oldParams.POLAR_UP = getComplects(Complects::POLAR_UP) == 2 ? true : false;

    oldParams.LIU = getSwap(Swap::LIU);
    oldParams.CONVERTER_UP_COMPLECT_1 = getSwap(Swap::CONVERTER_UP_COMPLECT_1);
    oldParams.CONVERTER_DOWN_COMPLECT_2 = getSwap(Swap::CONVERTER_DOWN_COMPLECT_2);
    oldParams.CONVERTER_DOWN_COMPLECT_1 = getSwap(Swap::CONVERTER_DOWN_COMPLECT_1);
    oldParams.NP_2 = getSwap(Swap::NP_2);
    oldParams.NP_1 = getSwap(Swap::NP_1);
    oldParams.NP = getSwap(Swap::NP);
    oldParams.AYY495_COMPLECT_1 = getSwap(Swap::AYY495_COMPLECT_1);
    oldParams.AYY495_COMPLECT_2 = getSwap(Swap::AYY495_COMPLECT_2);
    oldParams.TEST_TRANSLATION = getSwap(Swap::TEST_TRANSLATION);
    oldParams.ANT = getSwap(Swap::ANT);
    oldParams.SCU1 = getSwap(Swap::SCU1);
    oldParams.SCU2 = getSwap(Swap::SCU2);

    oldParams.MANUAL = getModeANT(ModeANT::MANUAL);
    oldParams.PROGRAMM = getModeANT(ModeANT::PROGRAMM);
    oldParams.CORRECTION = getModeANT(ModeANT::CORRECTION);
    oldParams.TD = getModeANT(ModeANT::TD);
    oldParams.CALIBRATION = getModeANT(ModeANT::CALIBRATION);

    oldParams.CHANGE_DISTANCE = getModeORM(ModeORM::CHANGE_DISTANCE);
    oldParams.CHANGE_ANGLE = getModeORM(ModeORM::CHANGE_ANGLE);
    oldParams.ID_ORM = getModeORM(ModeORM::ID_ORM);

    return oldParams;
}

void BaseFunctionControl::setInfoControl(StructFunctionControl *infoControl)
{
    QMutexLocker lock(&_mutex);
    _infoControl = infoControl;
}


