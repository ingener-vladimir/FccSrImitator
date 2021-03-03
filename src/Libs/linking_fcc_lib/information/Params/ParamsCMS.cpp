#include "linkingFcc/infornation/Params/ParamsCMS.h"

#include <QDateTime>

ParamsCMS::ParamsCMS()
{
    initStateComplects();
    _functionControl = new StructFunctionControl();
    infoFC = QSharedPointer<InfoFunctionControl>(new InfoFunctionControl(_functionControl));
    commands = QSharedPointer<CommandControl>(new CommandControl());
}

ParamsCMS::~ParamsCMS()
{
    delete _functionControl;
    if(infoFC)
    {
        infoFC.reset();
        infoFC = nullptr;
    }

    if(commands)
    {
        commands.reset();
        commands = nullptr;
    }
}

QJsonObject ParamsCMS::serializeToJSON()
{
    // состояние КИС
    QJsonObject object;
    object.insert(getIsConnectedFCCFieldName(), QJsonValue(getIsConnectedFCC()));
    object.insert(getNumberKAFieldName(), QJsonValue(getNumberKA()));
    object.insert(getNumberSeansFieldName(), QJsonValue(getNumberSeans()));
    object.insert(getNumberVitokFieldName(), QJsonValue(getNumberVitok()));
    object.insert(getTimeCMSFieldName(), QJsonValue(static_cast<qint64>(getInfoFC()->getRefInfoControl()->getCurrentTime())));
    object.insert(getTimeNPFieldName(), QJsonValue(static_cast<qint64>(getInfoFC()->getRefInfoControl()->getDigitizationTime())));
    object.insert(getDiscrepancyFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getOffsetTime()));
    object.insert(getModeWorkPFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::MODE_WORK)));
    object.insert(getModePrepareFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::MODE_PREPARE)));
    object.insert(getModeIFFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::MODE_IMIT_IF)));
    object.insert(getModeHFFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::MODE_IMIT_HF)));
    object.insert(getRadiationElev1FieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::RADIATION_AMPLIFIER_1)));
    object.insert(getRadiationElev2FieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::RADIATION_AMPLIFIER_2)));
    object.insert(getLockCarrierFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::LOCK_CARRIER)));
    object.insert(getLockPNSFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::LOCK_PNS)));
    object.insert(getRadiationFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::MODEM_RADIATION)));
    object.insert(getModulationPNSFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::MODULATION_PNS)));
    object.insert(getControlFieldName(), QJsonValue(getControlCRT()));
    object.insert(getLevelSignalFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getSignalPower()));
    object.insert(getDeviationFreqFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getFrequencyDeviation()));

    // АС
    object.insert(getAzimuthFBSFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getStringAzimuthFBS()));
    object.insert(getAzimuthProgrammFieldName(), QJsonValue(getStringAzimuthProgramm()));
    object.insert(getAzimuthCorrectionFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getStringCorrectionAzimuth()));
    object.insert(getElevFBSFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getStringElevationFBS()));
    object.insert(getElevProgrammFieldName(), QJsonValue(getStringElevProgramm()));
    object.insert(getElevCorrectionFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getStringCorrectionElevation()));
    object.insert(getIsCorrectionFieldName(), QJsonValue(getIsCorrection()));
    object.insert(getLevelPTNFieldName(), QJsonValue(getLevelPTN()));
    object.insert(getIsTDFieldName(), QJsonValue(getIsAntennaTD()));
    object.insert(getCalibrationModeFieldName(), QJsonValue(getCalibrationMode()));

    object.insert("acMode_manual", QJsonValue(getInfoFC()->getModeANT(ModeANT::MANUAL)));
    object.insert("acMode_progr", QJsonValue(getInfoFC()->getModeANT(ModeANT::PROGRAMM)));
    object.insert("acMode_auto", QJsonValue(getInfoFC()->getModeANT(ModeANT::AUTOTRACKING)));
    object.insert("acMode_calibration", QJsonValue(getInfoFC()->getModeANT(ModeANT::CALIBRATION)));
    object.insert("isFCCControl", QJsonValue(getInfoFC()->getSystemState(SystemState::READY_ES)));

    // усилители мощности
    object.insert(getPowerFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getPowerReceiver()));
    object.insert(getAttFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getAttenuator()));
    object.insert(getTempFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTempReceiver()));
    auto prd = getInfoFC()->getSystemState(SystemState::TRANSMITTER);
    object.insert(getPRDinAntFieldName(), QJsonValue(prd));
    object.insert(getPRDinLoadFieldName(), QJsonValue(!prd));

    // комплекты
    for(auto& key : stateComplects.keys())
    {
        auto name = getNameComplectForJson(key);
        if(key == 0)
        {
            if(_isModemCortex)
            {
                object.insert(name, QJsonValue(3));
                continue;
            }
        }
        uint8_t comp{0};
        if(stateComplects.value(key))
            comp = getInfoFC()->getComplects(static_cast<Complects>(key));
        object.insert(name, QJsonValue(comp));
    }

    object.insert(getPolarPLMFieldName(), QJsonValue(getInfoFC()->getComplects(Complects::POLAR_RECEIVER)));
    object.insert(getPolarUpFieldName(), QJsonValue(getInfoFC()->getComplects(Complects::POLAR_UP)));
    object.insert(getSwapLIUFieldName(), QJsonValue(getInfoFC()->getSwap(Swap::LIU)));

    // настройки КИС
    object.insert(getLiterCarrierFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getLiter()));
    object.insert(getLiterPNSFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getLiterPNS()));
    object.insert(getLiterOTCFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getLiterOTC()));
    object.insert(getStripPRMFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getBandReceiver()));
    object.insert(getCorrectionSearchFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getSearchCorrection()));
    object.insert(getCorrectionDoplerFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getDoplerCorrection()));
    object.insert(getKeySCPIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getKeySCPI()));
    object.insert(getKeyOSKFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getKeyOSK()));
    object.insert(getCloseModeFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::MODE_CLOSE)));

    // компенсация блокера
    object.insert(getDoplerByCUFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::DOPLER_COMPLECT_TD)));
    object.insert(getDoplerByAnswerFieldName(), QJsonValue(getInfoFC()->getSystemState(SystemState::DOPLER_COMPLECT_ANSWER)));
    object.insert(getIdCUFieldName(), getIdCU());
    object.insert(getLockAnswerFieldName(), getLockAnswer());
    object.insert(getDoplerTimeTDFieldName(), QJsonValue(static_cast<qint64>(getDoplerTimeTD())));
    object.insert(getCompensationCarrierTDFieldName(), QJsonValue(getCompensationCarrierTD()));
    object.insert(getCompensationPNSTDFieldName(), QJsonValue(getCompensationPNSTD()));
    object.insert(getDoplerTimeAnswerFieldName(), QJsonValue(static_cast<qint64>(getDoplerTimeAnswer())));
    object.insert(getCompensationCarrierAnswerFieldName(), QJsonValue(getCompensationCarrierAnswer()));
    object.insert(getCompensationPNSAnswerFieldName(), QJsonValue(getCompensationPNSAnswer()));
    object.insert(getDopplerPNCorrectionFieldName(), QJsonValue(getDopplerPNCorrection()));

    //ТМИ
    object.insert(getMode1kHzFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getModeTLM(ModeTLM::TLM_1KHZ)));
    object.insert(getMode8kHzFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getModeTLM(ModeTLM::TLM_8KHZ)));
    object.insert(getCounterTLMFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getCounterTLM()));

    /// РК
    auto isOrk = getInfoFC()->getRefInfoControl()->getTicketOTC(TicketOTC::PROCESS_OOTC);
    auto ticket = getInfoFC()->getRefInfoControl()->getNumberTicketedOTC();//getSingleCommand().numberCommand();
    object.insert(getNumberOTCFieldName(), QJsonValue(ticket));
    object.insert(getFirstSemiKitFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getDecoder(OnboardDecoder::HS1)));
    object.insert(getSecondSemiKitFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getDecoder(OnboardDecoder::HS2)));
    object.insert(getPlusOTCFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketOTC(TicketOTC::PLUS)));
    object.insert(getMinusOTCFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketOTC(TicketOTC::MINUS)));
    object.insert(getNullOTCFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketOTC(TicketOTC::NULL_OTC)));
    object.insert(getSendOTCFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketOTC(TicketOTC::PROCESS)));
    object.insert(getOOTCFieldName(), QJsonValue(isOrk));
    object.insert("REalCMDNum", QJsonValue(getRealCMDNum()));

    /// СИ
    object.insert(getNumberSIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getIdSI()));
    object.insert(getNumberPhraseSIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getNumberTicketedSI()));
    object.insert(getPlusSIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::PLUS)));
    object.insert(getMinusSIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::MINUS)));
    object.insert(getNullSIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::NULL_SI)));
    object.insert(getNullZKVIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::NULL_ZKV)));
    object.insert(getOnSIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::ON_SI)));
    object.insert(getStopSIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::STOP_SI)));
    object.insert(getIdSIFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::PROCESS_SI)));

    // РКО
    auto curTemp{0};
    if(getInfoFC()->getModeORM(ModeORM::SEC_1))
        curTemp = 1;
    else if(getInfoFC()->getModeORM(ModeORM::SEC_10))
        curTemp = 10;
    else if(getInfoFC()->getModeORM(ModeORM::SEC_20))
        curTemp = 20;
    object.insert(getCurrentTempORMFieldName(), QJsonValue(curTemp));
    object.insert(getCounterAngleFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getCounterAngle()));
    object.insert(getCounterDistanceFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getCounterDistance()));
    object.insert(getChangeDistanceFieldName(), QJsonValue(getInfoFC()->getModeORM(ModeORM::CHANGE_DISTANCE)));
    object.insert(getChangeAngleFieldName(), QJsonValue(getInfoFC()->getModeORM(ModeORM::CHANGE_ANGLE)));
    object.insert(getIdDZFieldName(), QJsonValue(getIsModemTD()));
    object.insert(getCalibrationFieldName(), QJsonValue(false));

    object.insert(getIsSendingSingleCmdFieldName(), QJsonValue(getInfoFC()->getRefInfoControl()->getTicketOTC(TicketOTC::PROCESS)));
    object.insert(getIsSendingSpecialSingleCmdFieldName(), QJsonValue(isOrk));

    object.insert(getMSHUComplectFieldName(), QJsonValue(getMSHUComplect()));

    return object;
}

int ParamsCMS::getRealCMDNum() {
    return _realCMDNum;
}

void ParamsCMS::setRealCMDNum(int v) {
    _realCMDNum = v;
}

int16_t ParamsCMS::getMSHUComplect() const
{
    QMutexLocker lock(&_mutex);
    return _complectMSHU;
}
void ParamsCMS::setMSHUComplect(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    _complectMSHU = value;
}

QString ParamsCMS::getNameComplectForJson(const uint8_t comp)
{
    QString name{""};
    switch(static_cast<Complects>(comp))
    {
    case Complects::MODEM:
    {
        name = getComplectModemFieldName();
        break;
    }

    case Complects::CONVERTER_UP:
    {
        name = getComplectConverterFieldName();
        break;
    }

    case Complects::AMPLIFIER:
    {
        name = getComplectYMFieldName();
        break;
    }

    case Complects::MSHY:
    {
        name = getComplectMSHYFieldName();
        break;
    }
    default:
        break;
    }
    return name;
}

void ParamsCMS::setParamsSession(const int16_t KA, const int16_t seans, const int16_t vitok)
{
    setNumberKA(KA);
    setNumberSeans(seans);
    setNumberVitok(vitok);
}

void ParamsCMS::setDefaultParams()
{
    setNumberKA(0);
    setNumberSeans(0);
    setNumberVitok(0);
}

bool ParamsCMS::getIsConnectedFCC() const
{
    return isConnectedFCC;
}

void ParamsCMS::setIsConnectedFCC(bool value)
{
    isConnectedFCC = value;
}

int16_t ParamsCMS::getNumberKA() const
{
    QMutexLocker lock(&_mutex);
    return numberKA;
}

void ParamsCMS::setNumberKA()
{
    QMutexLocker lock(&_mutex);
    numberKA = commands->numKA();
}

void ParamsCMS::setNumberKA(const int16_t KA)
{
    QMutexLocker lock(&_mutex);
    numberKA = KA;
}

void ParamsCMS::setParamsSession()
{
    QMutexLocker lock(&_mutex);
    numberSeans = commands->getParamsSession().numberSeans;
    numberVitok = commands->getParamsSession().numberVitok;
}

int16_t ParamsCMS::getNumberSeans() const
{
    QMutexLocker lock(&_mutex);
    return numberSeans;
}

void ParamsCMS::setNumberSeans(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    numberSeans = value;
}

int16_t ParamsCMS::getNumberVitok() const
{
    QMutexLocker lock(&_mutex);
    return numberVitok;
}

void ParamsCMS::setNumberVitok(const int16_t &value)
{
    QMutexLocker lock(&_mutex);
    numberVitok = value;
}

int16_t ParamsCMS::getNumberNIP() const
{
    return numberNIP;
}

void ParamsCMS::setNumberNIP(const int16_t &value)
{
    numberNIP = value;
}

QSharedPointer<BaseFunctionControl> ParamsCMS::getInfoFC()
{
    QMutexLocker lock(&_mutex);
    return infoFC;
}

void ParamsCMS::setInfoFC(QSharedPointer<BaseFunctionControl> value)
{
    QMutexLocker lock(&_mutex);
    infoFC.reset();
    infoFC = nullptr;
    infoFC = value;
}

void ParamsCMS::createByteArrayForSendIFCT(QByteArray &array)
{
    getInfoFC()->createByteArray(array);
}

bool ParamsCMS::getControlCRT() const
{
    return controlCRT;
}

void ParamsCMS::setControlCRT(bool value)
{
    controlCRT = value;
    getInfoFC()->setSystemState(SystemState::READY_ES, !value);
}

double ParamsCMS::getAzimuthProgramm() const
{
    QMutexLocker lock(&_mutex);
    return azimuthProgramm;
}

QString ParamsCMS::getStringAzimuthProgramm() const
{
    daq::Degree degree(getAzimuthProgramm());
    QString deg{degree.toString()};
    return deg;
}

void ParamsCMS::setAzimuthProgramm(const double &value)
{
    QMutexLocker lock(&_mutex);
    azimuthProgramm = value;
}

double ParamsCMS::getElevProgramm() const
{
    QMutexLocker lock(&_mutex);
    return elevProgramm;
}

QString ParamsCMS::getStringElevProgramm() const
{
    daq::Degree degree(getElevProgramm());
    QString deg{degree.toString()};
    return deg;
}

void ParamsCMS::setElevProgramm(const double &value)
{
    QMutexLocker lock(&_mutex);
    elevProgramm = value;
}

bool ParamsCMS::getIsCorrection() const
{
    QMutexLocker lock(&_mutex);
    return isCorrection;
}

void ParamsCMS::setIsCorrection(bool value)
{
    QMutexLocker lock(&_mutex);
    isCorrection = value;
}

double ParamsCMS::getLevelPTN() const
{
    QMutexLocker lock(&_mutex);
    return levelPTN;
}

void ParamsCMS::setLevelPTN(const double &value)
{
    QMutexLocker lock(&_mutex);
    levelPTN = value;
}

bool ParamsCMS::getIsAntennaTD() const
{
    QMutexLocker lock(&_mutex);
    return isAntennaTD;
}

void ParamsCMS::setIsAntennaTD(bool value)
{
    QMutexLocker lock(&_mutex);
    isAntennaTD = value;
}

void ParamsCMS::changeStateComplect(const Complects comp, const bool state)
{
    stateComplects[static_cast<uint8_t>(comp)] = state;
}

bool ParamsCMS::getIdCU() const
{
    QMutexLocker lock(&_mutex);
    return idCU;
}

void ParamsCMS::setIdCU(bool value)
{
    QMutexLocker lock(&_mutex);
    idCU = value;
}

bool ParamsCMS::getLockAnswer() const
{
    QMutexLocker lock(&_mutex);
    return lockAnswer;
}

void ParamsCMS::setLockAnswer(bool value)
{
    QMutexLocker lock(&_mutex);
    lockAnswer = value;
}

uint64_t ParamsCMS::getDoplerTimeTD() const
{
    QMutexLocker lock(&_mutex);
    return doplerTimeTD;
}

void ParamsCMS::setDoplerTimeTD(const uint64_t &value)
{
    QMutexLocker lock(&_mutex);
    doplerTimeTD = value;
}

double ParamsCMS::getCompensationCarrierTD() const
{
    QMutexLocker lock(&_mutex);
    return compensationCarrierTD;
}

void ParamsCMS::setCompensationCarrierTD(const double &value)
{
    QMutexLocker lock(&_mutex);
    compensationCarrierTD = value;
}

double ParamsCMS::getCompensationPNSTD() const
{
    QMutexLocker lock(&_mutex);
    return compensationPNSTD;
}

void ParamsCMS::setCompensationPNSTD(const double &value)
{
    QMutexLocker lock(&_mutex);
    compensationPNSTD = value;
}

uint64_t ParamsCMS::getDoplerTimeAnswer() const
{
    QMutexLocker lock(&_mutex);
    return doplerTimeAnswer;
}

void ParamsCMS::setDoplerTimeAnswer(const uint64_t &value)
{
    QMutexLocker lock(&_mutex);
    doplerTimeAnswer = value;
}

double ParamsCMS::getCompensationCarrierAnswer() const
{
    QMutexLocker lock(&_mutex);
    return compensationCarrierAnswer;
}

void ParamsCMS::setCompensationCarrierAnswer(const double &value)
{
    QMutexLocker lock(&_mutex);
    compensationCarrierAnswer = value;
}

double ParamsCMS::getCompensationPNSAnswer() const
{
    QMutexLocker lock(&_mutex);
    return compensationPNSAnswer;
}

void ParamsCMS::setCompensationPNSAnswer(const double &value)
{
    QMutexLocker lock(&_mutex);
    compensationPNSAnswer = value;
}

bool ParamsCMS::getControl() const
{
    return control;
}

void ParamsCMS::setControl(bool value)
{
    control = value;
    getInfoFC()->setSystemState(SystemState::READY_ES, value);
}

BaseCommandControl& ParamsCMS::getCommands()
{
    return *commands;
}

void ParamsCMS::setCommands(QSharedPointer<BaseCommandControl> value)
{
    commands.reset();
    commands = nullptr;
    commands = value;
}

CommandsControl ParamsCMS::getCurrentCommandControl()
{
    return commands->numCommand();
}

QJsonObject ParamsCMS::getJsonCommandControl()
{
    return commands->vectorData();
}

void ParamsCMS::setCurrentModeStation(const uint16_t currentMode)
{
    commands->setCurrentMode(currentMode);
}

int16_t ParamsCMS::getParamCommandControl(const Words word)
{
    return commands->getParam(word);
}

void ParamsCMS::setTypeSender(const TypeSender sender)
{
    commands->setCurrentType(sender);
}

TypeSender ParamsCMS::getTypeSender() const
{
    return commands->getCurrentType();
}

SpecialInformation &ParamsCMS::getSpecialInfo()
{
    return specialInfo;
}

QString ParamsCMS::getConvertPhraseSpecialInformation()
{
    return specialInfo.getConvertPhrase();
}

bool ParamsCMS::unserializeSpecialInformation(QByteArray &array)
{
    return specialInfo.unserializeSpecialInformation(array);
}

SingleCommand &ParamsCMS::getSingleCommand()
{
    return singleCommand;
}

void ParamsCMS::setNumberSingleCommand(const uint16_t numCommand)
{
    singleCommand.setNumberCommand(numCommand);
}

void ParamsCMS::setTypeSingleCommand(const bool typeCommand)
{
    singleCommand.setTypeCommand(typeCommand);
}

void ParamsCMS::setTypeTimeSingleCommand(const bool typeTime)
{
    singleCommand.setTypeTimeDelivery(typeTime);
}

void ParamsCMS::setDateTimeSingleCommand(const QString dateTime)
{
    singleCommand.setDateTime(dateTime);
}

QJsonObject ParamsCMS::getJsonSpecialCC()
{
    return specialCC.vectorData();
}

SpecialCC &ParamsCMS::getSpecialCC()
{
    return specialCC;
}

void ParamsCMS::setSpecialCC(const SpecialCC &value)
{
    specialCC = value;
}

bool ParamsCMS::getIsModemTD() const
{
    QMutexLocker lock(&_mutex);
    return isModemTD;
}

void ParamsCMS::setIsModemTD(bool value)
{
    QMutexLocker lock(&_mutex);
    isModemTD = value;
}

void ParamsCMS::setIsModemCortex(bool isModemCortex)
{
    _isModemCortex = isModemCortex;
}

bool ParamsCMS::getIsSendingSpecialSingleCmd() const
{
    QMutexLocker lock(&_mutex);
    return _isSendingSpecialSingleCmd;
}

void ParamsCMS::setIsSendingSpecialSingleCmd(bool value)
{
    QMutexLocker lock(&_mutex);
    _isSendingSpecialSingleCmd = value;
}

bool ParamsCMS::getIsSendingSingleCmd() const
{
    QMutexLocker lock(&_mutex);
    return _isSendingSingleCmd;
}

void ParamsCMS::setDopplerPNCorrection(const double &value) {
    _dopplerPNCorrection = value;
}

double ParamsCMS::getDopplerPNCorrection() const {
    return _dopplerPNCorrection;
}

void ParamsCMS::setCalibrationMode(const bool &value) {
    isCalibrationMode = value;
}

bool ParamsCMS::getCalibrationMode() const {
    return isCalibrationMode;
}

void ParamsCMS::setIsSendingSingleCmd(bool value)
{
    QMutexLocker lock(&_mutex);
    _isSendingSingleCmd = value;
}

void ParamsCMS::resetParams()
{
    setNumberKA(0);
    setNumberSeans(0);
    setNumberVitok(0);
    setControl(false);
    setControlCRT(false);
    setAzimuthProgramm(0.0);
    setElevProgramm(0.0);
    setIsCorrection(false);
    setLevelPTN(0.0);
    setIsAntennaTD(false);
    setIsModemTD(false);
    setCalibrationMode(false);
    setIdCU(false);
    setLockAnswer(false);
    setDoplerTimeTD(0);
    setCompensationCarrierTD(false);
    setCompensationPNSTD(0.0);
    setDoplerTimeAnswer(0);
    setCompensationCarrierAnswer(0.0);
    setCompensationPNSAnswer(0.0);

    setIsModemCortex(false);
    setIsSendingSingleCmd(false);
    setIsSendingSpecialSingleCmd(false);
    setDopplerPNCorrection(0.0);
    setMSHUComplect(0);
    setRealCMDNum(0);

    getInfoFC()->getRefInfoControl()->resetInfoFunctionControl();
    commands->resetCommandControl();
    specialInfo.resetSI();
    singleCommand.resetSC();
    specialCC.resetSpecialCC();

    initStateComplects();
}

void ParamsCMS::initStateComplects()
{
    stateComplects.insert(static_cast<uint8_t>(Complects::MODEM), false);
    stateComplects.insert(static_cast<uint8_t>(Complects::CONVERTER_UP), false);
    stateComplects.insert(static_cast<uint8_t>(Complects::AMPLIFIER), false);
    stateComplects.insert(static_cast<uint8_t>(Complects::MSHY), false);
}

StructFunctionControl* ParamsCMS::getFunctionControl()
{
    return _functionControl;
}
