#include "linkingFcc/infornation/FunctionControl/StructFunctionControl.h"

StructFunctionControl::StructFunctionControl()
{

}

StructFunctionControl::StructFunctionControl(const StructFunctionControl &control)
{
    setCurrentTime(control.getCurrentTime());
    setDigitizationTime(control.getDigitizationTime());
    setOffsetTime(control.getOffsetTime());
    setValueSystemState(control.getValueSystemState());
    setLiter(control.getLiter());
    setBandReceiver(control.getBandReceiver());
    setSearchCorrection(control.getSearchCorrection());
    setDoplerCorrection(control.getDoplerCorrection());
    setLiterPNS(control.getLiterPNS());
    setLiterOTC(control.getLiterOTC());
    setDecoder(control.getDecoder());
    setSignalPower(control.getSignalPower());
    setValueComplects(control.getValueComplects());
    setValueModeANT(control.getValueModeANT());
    setAzimuthFBS(control.getAzimuthFBS());
    setElevationFBS(control.getElevationFBS());
    setCorrectionAzimuth(control.getCorrectionAzimuth());
    setCorrectionElevation(control.getCorrectionElevation());
    setPointAzimuth(control.getPointAzimuth());
    setPointElevation(control.getPointElevation());
    setKeySCPI(control.getKeySCPI());
    setKeyOSK(control.getKeyOSK());
    setWord33(control.getWord33());
    setWord34(control.getWord34());
    setWord35(control.getWord35());
    setTicketOTC(control.getTicketOTC());
    setNumberTicketedOTC(control.getNumberTicketedOTC());
    setTicketSI(control.getTicketSI());
    setNumberTicketedSI(control.getNumberTicketedSI());
    setIdSI(control.getIdSI());
    setCounterTLM(control.getCounterTLM());
    setValueModeORM(control.getValueModeORM());
    setCounterAngle(control.getCounterAngle());
    setCounterDistance(control.getCounterDistance());
    setDoplerCorrection(control.getDoplerCorrection());
    setFrequencyDeviation(control.getFrequencyDeviation());
    setAlarmDevices(control.getAlarmDevice());
    setPowerReceiver(control.getPowerReceiver());
    setAttenuator(control.getAttenuator());
    setTempReceiver(control.getTempReceiver());
}

StructFunctionControl &StructFunctionControl::operator=(const StructFunctionControl &control)
{
    if(this != &control)
    {
        setCurrentTime(control.getCurrentTime());
        setDigitizationTime(control.getDigitizationTime());
        setOffsetTime(control.getOffsetTime());
        setValueSystemState(control.getValueSystemState());
        setLiter(control.getLiter());
        setBandReceiver(control.getBandReceiver());
        setSearchCorrection(control.getSearchCorrection());
        setDoplerCorrection(control.getDoplerCorrection());
        setLiterPNS(control.getLiterPNS());
        setLiterOTC(control.getLiterOTC());
        setDecoder(control.getDecoder());
        setSignalPower(control.getSignalPower());
        setValueComplects(control.getValueComplects());
        setValueModeANT(control.getValueModeANT());
        setAzimuthFBS(control.getAzimuthFBS());
        setElevationFBS(control.getElevationFBS());
        setCorrectionAzimuth(control.getCorrectionAzimuth());
        setCorrectionElevation(control.getCorrectionElevation());
        setPointAzimuth(control.getPointAzimuth());
        setPointElevation(control.getPointElevation());
        setKeySCPI(control.getKeySCPI());
        setKeyOSK(control.getKeyOSK());
        setWord33(control.getWord33());
        setWord34(control.getWord34());
        setWord35(control.getWord35());
        setTicketOTC(control.getTicketOTC());
        setNumberTicketedOTC(control.getNumberTicketedOTC());
        setTicketSI(control.getTicketSI());
        setNumberTicketedSI(control.getNumberTicketedSI());
        setIdSI(control.getIdSI());
        setCounterTLM(control.getCounterTLM());
        setValueModeORM(control.getValueModeORM());
        setCounterAngle(control.getCounterAngle());
        setCounterDistance(control.getCounterDistance());
        setDoplerCorrection(control.getDoplerCorrection());
        setFrequencyDeviation(control.getFrequencyDeviation());
        setAlarmDevices(control.getAlarmDevice());
        setPowerReceiver(control.getPowerReceiver());
        setAttenuator(control.getAttenuator());
        setTempReceiver(control.getTempReceiver());
    }

    return *this;
}

bool StructFunctionControl::getSystemState(const uint8_t index)
{
    return getValueParamStation<uint16_t>(systemState, index);
}

void StructFunctionControl::setSystemState(const uint8_t mode, const bool state)
{
    setValueParamStation<uint16_t>(systemState, mode, state);
}

uint8_t StructFunctionControl::getComplects(const uint8_t index)
{
    bool comp = getValueParamStation<uint16_t>(complects, index);
    return (comp) ? 2 : 1;
}

void StructFunctionControl::setComplects(const uint8_t complect, const bool state)
{
    setValueParamStation<uint16_t>(complects, complect, state);
}

bool StructFunctionControl::getSwap(const uint8_t index)
{
    return getValueParamStation<uint16_t>(swap, index);
}

void StructFunctionControl::setSwap(const uint8_t numSwap, const bool state)
{
    setValueParamStation<uint16_t>(swap, numSwap, state);
}

bool StructFunctionControl::getModeANT(const uint8_t mode)
{
    return getValueParamStation<int16_t>(modeANT, mode);
}

void StructFunctionControl::setModeANT(const uint8_t mode, const bool state)
{
    setValueParamStation<int16_t>(modeANT, mode, state);
}

uint16_t StructFunctionControl::getWord33() const
{
    QMutexLocker lock(&_mutex);
    return word33;
}

uint16_t StructFunctionControl::getSwitch(const Switches &value) const
{
    return getValueParamStation<uint16_t>(word33, static_cast<uint8_t>(value));
}

void StructFunctionControl::setSwitch(const Switches &value, const bool state)
{
    setValueParamStation<uint16_t>(word33, static_cast<uint8_t>(value), state);
}

uint16_t StructFunctionControl::getValueSystemState() const
{
    QMutexLocker lock(&_mutex);
    return systemState;
}

uint16_t StructFunctionControl::getValueComplects() const
{
    QMutexLocker lock(&_mutex);
    return complects;
}

uint16_t StructFunctionControl::getValueSwap() const
{
    QMutexLocker lock(&_mutex);
    return swap;
}

int16_t StructFunctionControl::getValueModeANT() const
{
    QMutexLocker lock(&_mutex);
    return modeANT;
}

uint16_t StructFunctionControl::getValueModeORM() const
{
    QMutexLocker lock(&_mutex);
    return modeORM;
}

uint64_t StructFunctionControl::getCurrentTime() const
{
    QMutexLocker lock(&_mutex);
    return currentTime;
}

void StructFunctionControl::setCurrentTime(const uint64_t &value)
{
    QMutexLocker lock(&_mutex);
    currentTime = value;
}

uint64_t StructFunctionControl::getDigitizationTime() const
{
    QMutexLocker lock(&_mutex);
    return digitizationTime;
}

void StructFunctionControl::setDigitizationTime(const uint64_t &value)
{
    QMutexLocker lock(&_mutex);
    digitizationTime = value;
}

int32_t StructFunctionControl::getOffsetTime() const
{
    QMutexLocker lock(&_mutex);
    return offsetTime;
}

void StructFunctionControl::setOffsetTime(const int32_t &value)
{
    QMutexLocker lock(&_mutex);
    offsetTime = value;
}

uint16_t StructFunctionControl::getLiter() const
{
    QMutexLocker lock(&_mutex);
    return liter;
}

void StructFunctionControl::setLiter(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    liter = value;
}

uint16_t StructFunctionControl::getBandReceiver() const
{
    QMutexLocker lock(&_mutex);
    return bandReceiver;
}

void StructFunctionControl::setBandReceiver(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    bandReceiver = value;
}

int16_t StructFunctionControl::getSearchCorrection() const
{
    QMutexLocker lock(&_mutex);
    return searchCorrection;
}

void StructFunctionControl::setSearchCorrection(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    searchCorrection = (value);
}

int16_t StructFunctionControl::getDoplerCorrection() const
{
    QMutexLocker lock(&_mutex);
    return doplerCorrection;
}

void StructFunctionControl::setDoplerCorrection(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    doplerCorrection = value;
}

uint16_t StructFunctionControl::getLiterPNS() const
{
    QMutexLocker lock(&_mutex);
    return literPNS;
}

void StructFunctionControl::setLiterPNS(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    literPNS = value;
}

uint16_t StructFunctionControl::getLiterOTC() const
{
    QMutexLocker lock(&_mutex);
    return literOTC;
}

void StructFunctionControl::setLiterOTC(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    literOTC = value;
}

bool StructFunctionControl::getDecoder(const OnboardDecoder numDecoder) const
{
    return getValueParamStation<uint16_t>(decoder, static_cast<uint8_t>(numDecoder));
}

uint16_t StructFunctionControl::getDecoder() const
{
    QMutexLocker lock(&_mutex);
    return decoder;
}

void StructFunctionControl::setDecoder(OnboardDecoder numDecoder, bool state)
{
    setValueParamStation<uint16_t>(decoder, static_cast<uint8_t>(numDecoder), state);
}

void StructFunctionControl::setDecoder(const uint16_t dec)
{
    QMutexLocker lock(&_mutex);
    decoder = dec;
}

int16_t StructFunctionControl::getSignalPower() const
{
    QMutexLocker lock(&_mutex);
    return signalPower;
}

void StructFunctionControl::setSignalPower(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    signalPower = value;
}

double StructFunctionControl::getAzimuthFBS() const
{
    QMutexLocker lock(&_mutex);
    return azimuthFBS;
}

QString StructFunctionControl::getStringAzimuthFBS() const
{
    daq::Degree degree(getAzimuthFBS());
    QString deg{degree.toString()};
    return deg;
}

void StructFunctionControl::setAzimuthFBS(const double &value)
{
    QMutexLocker lock(&_mutex);
    azimuthFBS = value;
}

double StructFunctionControl::getElevationFBS() const
{
    QMutexLocker lock(&_mutex);
    return elevationFBS;
}

QString StructFunctionControl::getStringElevationFBS() const
{
    daq::Degree degree(getElevationFBS());
    QString deg{degree.toString()};
    return deg;
}

void StructFunctionControl::setElevationFBS(const double &value)
{
    QMutexLocker lock(&_mutex);
    elevationFBS = value;
}

double StructFunctionControl::getCorrectionAzimuth() const
{
    QMutexLocker lock(&_mutex);
    return correctionAzimuth;
}

QString StructFunctionControl::getStringCorrectionAzimuth() const
{
    daq::Degree degree(getCorrectionAzimuth());
    QString deg{degree.toString()};
    return deg;
}

void StructFunctionControl::setCorrectionAzimuth(const double &value)
{
    QMutexLocker lock(&_mutex);
    correctionAzimuth = value;
}

double StructFunctionControl::getCorrectionElevation() const
{
    QMutexLocker lock(&_mutex);
    return correctionElevation;
}

QString StructFunctionControl::getStringCorrectionElevation() const
{
    daq::Degree degree(getCorrectionElevation());
    QString deg{degree.toString()};
    return deg;
}

void StructFunctionControl::setCorrectionElevation(const double &value)
{
    QMutexLocker lock(&_mutex);
    correctionElevation = value;
}

double StructFunctionControl::getPointAzimuth() const
{
    QMutexLocker lock(&_mutex);
    return pointAzimuth;
}

void StructFunctionControl::setPointAzimuth(const double &value)
{
    QMutexLocker lock(&_mutex);
    pointAzimuth = value;
}

double StructFunctionControl::getPointElevation() const
{
    QMutexLocker lock(&_mutex);
    return pointElevation;
}

void StructFunctionControl::setPointElevation(const double &value)
{
    QMutexLocker lock(&_mutex);
    pointElevation = value;
}

uint16_t StructFunctionControl::getKeySCPI() const
{
    QMutexLocker lock(&_mutex);
    return keySCPI;
}

void StructFunctionControl::setKeySCPI(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    keySCPI = value;
}

uint16_t StructFunctionControl::getKeyOSK() const
{
    QMutexLocker lock(&_mutex);
    return keyOSK;
}

void StructFunctionControl::setKeyOSK(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    keyOSK = value;
}

uint16_t StructFunctionControl::getWord34() const
{
    QMutexLocker lock(&_mutex);
    return reserve_2;
}

void StructFunctionControl::setWord34(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    reserve_2 = value;
}

uint8_t StructFunctionControl::getTemp() const
{
    QMutexLocker lock(&_mutex);
    return static_cast<uint8_t>(reserve_2);
}

void StructFunctionControl::setTemp(const int8_t temp)
{
    QMutexLocker lock(&_mutex);
    reserve_2 = (reserve_2 & 0xffff)  | (temp & 0xff);
}

uint8_t StructFunctionControl::getHumidity() const
{
    QMutexLocker lock(&_mutex);
    return static_cast<uint8_t>(reserve_2 >> 8);
}

void StructFunctionControl::setHumidity(const uint8_t humidity)
{
    QMutexLocker lock(&_mutex);
    reserve_2 = (reserve_2 & 0xff)  | (((humidity) << 8) & 0xFF00);
}

uint16_t StructFunctionControl::getWord35() const
{
    QMutexLocker lock(&_mutex);
    return reserve_3;
}

void StructFunctionControl::setWord35(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    reserve_3 = value;
}

uint8_t StructFunctionControl::getWindSpeed() const
{
    QMutexLocker lock(&_mutex);
    return (reserve_3 >> 9) & 0x7F;
}

void StructFunctionControl::setWindSpeed(const uint8_t &value)
{
    QMutexLocker lock(&_mutex);
    reserve_3 = (reserve_3 & 0x1FF) | ((value & 0x7F) << 9);
}

uint16_t StructFunctionControl::getWindDirection() const
{
    QMutexLocker lock(&_mutex);
    return (reserve_3 & 0x1FF);
}

void StructFunctionControl::setWindDirection(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    reserve_3 = (reserve_3 & 0xFE00) | (value & 0x1FF);
}

bool StructFunctionControl::getTicketOTC(const TicketOTC ticket) const
{
    return getValueParamStation<uint16_t>(ticketOTC, static_cast<uint8_t>(ticket));
}

uint16_t StructFunctionControl::getTicketOTC() const
{
    QMutexLocker lock(&_mutex);
    return ticketOTC;
}

void StructFunctionControl::setTicketOTC(const TicketOTC ticket, const bool state)
{
    setValueParamStation<uint16_t>(ticketOTC, static_cast<uint8_t>(ticket), state);
}

void StructFunctionControl::setTicketOTC(const uint16_t ticket)
{
    QMutexLocker lock(&_mutex);
    ticketOTC = ticket;
}

void StructFunctionControl::setTicketOTCFaultCounter(uint8_t value) {
    QMutexLocker lock(&_mutex);
    quint32 mask = (((0x01ul << 4) - 1) << 11);
    ticketOTC |= mask;
    ticketOTC &= ((value << 11)|(~mask));
}

uint16_t StructFunctionControl::getNumberTicketedOTC() const
{
    QMutexLocker lock(&_mutex);
    return numberTicketedOTC;
}

void StructFunctionControl::setNumberTicketedOTC(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    numberTicketedOTC = value;
}

bool StructFunctionControl::getTicketSI(const TicketSI ticket) const
{
    return getValueParamStation<uint16_t>(ticketSI, static_cast<uint8_t>(ticket));
}

uint16_t StructFunctionControl::getTicketSI() const
{
    QMutexLocker lock(&_mutex);
    return ticketSI;
}

void StructFunctionControl::setTicketSI(const TicketSI ticket, const bool state)
{
    setValueParamStation<uint16_t>(ticketSI, static_cast<uint8_t>(ticket), state);
}

void StructFunctionControl::setTicketSI(const uint16_t ticket)
{
    QMutexLocker lock(&_mutex);
    ticketSI = ticket;
}

uint16_t StructFunctionControl::getNumberTicketedSI() const
{
    QMutexLocker lock(&_mutex);
    return numberTicketedSI;
}

void StructFunctionControl::setNumberTicketedSI(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    numberTicketedSI = value;
}

uint16_t StructFunctionControl::getIdSI() const
{
    QMutexLocker lock(&_mutex);
    return idSI;
}

void StructFunctionControl::setIdSI(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    idSI = value;
}

bool StructFunctionControl::getModeTLM(const ModeTLM mode) const
{
    return getValueParamStation<uint16_t>(modeTLM, static_cast<uint8_t>(mode));
}

uint16_t StructFunctionControl::getModeTLM() const
{
    QMutexLocker lock(&_mutex);
    return modeTLM;
}

void StructFunctionControl::setModeTLM(const ModeTLM mode, const bool state)
{
    setValueParamStation<uint16_t>(modeTLM, static_cast<uint8_t>(mode), state);
}

void StructFunctionControl::resetModeTLM()
{
    setModeTLM(ModeTLM::TLM_1KHZ, false);
    setModeTLM(ModeTLM::TLM_8KHZ, false);
}

void StructFunctionControl::resetBandTLM()
{
    setModeTLM(ModeTLM::SLIM_STRIP, false);
    setModeTLM(ModeTLM::AVERAGE_STRIP, false);
    setModeTLM(ModeTLM::WIDE_STRIP, false);
}

uint16_t StructFunctionControl::getCounterTLM() const
{
    QMutexLocker lock(&_mutex);
    return counterTLM;
}

void StructFunctionControl::setCounterTLM(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    counterTLM = value;
}

bool StructFunctionControl::getModeORM(const uint8_t mode)
{
    return getValueParamStation<uint16_t>(modeORM, mode);
}

void StructFunctionControl::setModeORM(const uint8_t mode, const bool state)
{
    setValueParamStation<uint16_t>(modeORM, mode, state);
}

uint16_t StructFunctionControl::getCounterAngle() const
{
    QMutexLocker lock(&_mutex);
    return counterAngle;
}

void StructFunctionControl::setCounterAngle(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    counterAngle = value;
}

uint16_t StructFunctionControl::getCounterDistance() const
{
    QMutexLocker lock(&_mutex);
    return counterDistance;
}

void StructFunctionControl::setCounterDistance(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    counterDistance = value;
}

int16_t StructFunctionControl::getDopplerFreqPrediction() const
{
    QMutexLocker lock(&_mutex);
    return dopplerFreqPrediction;
}

void StructFunctionControl::setDopplerFreqPrediction(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    dopplerFreqPrediction = value;
}

int16_t StructFunctionControl::getFrequencyDeviation() const
{
    QMutexLocker lock(&_mutex);
    return frequencyDeviation;
}

void StructFunctionControl::setFrequencyDeviation(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    frequencyDeviation = value;
}

bool StructFunctionControl::getAlarmDevice(const AlarmDevices device) const
{
    return getValueParamStation<uint16_t>(alarmDevice, static_cast<uint8_t>(device));
}

uint16_t StructFunctionControl::getAlarmDevice() const
{
    QMutexLocker lock(&_mutex);
    return alarmDevice;
}

void StructFunctionControl::setAlarmDevices(const AlarmDevices device, const bool state)
{
    setValueParamStation<uint16_t>(alarmDevice, static_cast<uint8_t>(device), state);
}

void StructFunctionControl::setAlarmDevices(const uint16_t device)
{
    QMutexLocker lock(&_mutex);
    alarmDevice = device;
}

uint16_t StructFunctionControl::getPowerReceiver() const
{
    QMutexLocker lock(&_mutex);
    return powerReceiver;
}

void StructFunctionControl::setPowerReceiver(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    powerReceiver = value;
}

uint8_t StructFunctionControl::getAttenuator() const
{
    QMutexLocker lock(&_mutex);
    return attenuator;
}

void StructFunctionControl::setAttenuator(const uint16_t &value)
{
    QMutexLocker lock(&_mutex);
    attenuator = value;
}

int16_t StructFunctionControl::getTempReceiver() const
{
    QMutexLocker lock(&_mutex);
    return tempReceiver;
}

void StructFunctionControl::setTempReceiver(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    tempReceiver = value;
}

void StructFunctionControl::resetSwap()
{
    QMutexLocker lock(&_mutex);
    swap = 0;
}

void StructFunctionControl::setValueSystemState(const uint16_t state)
{
    QMutexLocker lock(&_mutex);
    systemState = state;
}

void StructFunctionControl::setValueComplects(const uint16_t state)
{
    QMutexLocker lock(&_mutex);
    complects = state;
}

void StructFunctionControl::setValueModeANT(const int16_t mode)
{
    QMutexLocker lock(&_mutex);
    modeANT = mode;
}

void StructFunctionControl::setValueModeORM(const uint16_t mode)
{
    QMutexLocker lock(&_mutex);
    modeORM = mode;
}

void StructFunctionControl::setWord33(const uint16_t state)
{
    QMutexLocker lock(&_mutex);
    word33 = state;
}

void StructFunctionControl::resetInfoFunctionControl()
{
    setCurrentTime(0);
    setDigitizationTime(0);
    setOffsetTime(0);
    setValueSystemState(0);
    setLiter(1);
    setBandReceiver(0);
    setSearchCorrection(0);
    setDoplerCorrection(0);
    setLiterPNS(0);
    setLiterOTC(0);
    setDecoder(0);
    setSignalPower(0);
    setValueComplects(0);
    resetSwap();
    setValueModeANT(0);
    setAzimuthFBS(0.0);
    setElevationFBS(0.0);
    setCorrectionAzimuth(0.0);
    setCorrectionElevation(0.0);
    setPointAzimuth(0.0);
    setPointElevation(0.0);
    setKeySCPI(0);
    setKeyOSK(0);
    setWord33(0);
    setWord34(0);
    setWord35(0);
    setTicketOTC(0);
    setNumberTicketedOTC(0);
    setTicketSI(0);
    setNumberTicketedSI(0);
    setIdSI(0);
    resetModeTLM();
    resetBandTLM();
    setCounterTLM(0);
    setValueModeORM(0);
    setCounterAngle(0);
    setCounterDistance(0);
    setDoplerCorrection(0);
    setFrequencyDeviation(0);
    setAlarmDevices(0);
    setPowerReceiver(0);
    setAttenuator(0);
    setTempReceiver(0);
}
