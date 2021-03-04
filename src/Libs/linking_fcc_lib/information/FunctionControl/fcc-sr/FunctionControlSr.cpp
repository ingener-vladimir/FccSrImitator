#include "linkingFcc/infornation/FunctionControl/fcc-sr/FunctionControlSr.h"
#include "utils/BitUtils.h"

uint16_t FunctionControlSr::getCounterTelemetry() const
{
    return _counterTelemetry.loadAcquire();
}

void FunctionControlSr::setCounterTelemetry(uint16_t value)
{
    _counterTelemetry.fetchAndStoreAcquire(value);
}

int32_t FunctionControlSr::getOffsetTime() const
{
    return _offsetTime.loadAcquire();
}

void FunctionControlSr::setOffsetTime(int value)
{
    _offsetTime.fetchAndStoreAcquire(value);
}

uint16_t FunctionControlSr::getLiter() const
{
    return _liter.loadAcquire();
}

void FunctionControlSr::setLiter(uint16_t value)
{
    _liter.fetchAndStoreAcquire(value);
}

uint16_t FunctionControlSr::getBandReceiver() const
{
    return _bandReceiver.loadAcquire();
}

void FunctionControlSr::setBandReceiver(uint16_t value)
{
    _bandReceiver.fetchAndStoreAcquire(value);
}

int16_t FunctionControlSr::getDoplerCorrection() const
{
    return _doplerCorrection.loadAcquire();
}

void FunctionControlSr::setDoplerCorrection(int16_t value)
{
    _doplerCorrection.fetchAndStoreAcquire(value);
}

uint16_t FunctionControlSr::getLiterPNS() const
{
    return _literPNS.loadAcquire();
}

void FunctionControlSr::setLiterPNS(uint16_t value)
{
    _literPNS.fetchAndStoreAcquire(value);
}

uint16_t FunctionControlSr::getLiterOTC() const
{
    return _literOTC.loadAcquire();
}

void FunctionControlSr::setLiterOTC(uint16_t value)
{
    _literOTC.fetchAndStoreAcquire(value);
}

int16_t FunctionControlSr::getSignalPower() const
{
    return _signalPower.loadAcquire();
}

void FunctionControlSr::setSignalPower(int16_t value)
{
    _signalPower.fetchAndStoreAcquire(value);
}

uint16_t FunctionControlSr::getNumberTicketedOTC() const
{
    return _numberTicketedOTC.loadAcquire();
}

void FunctionControlSr::setNumberTicketedOTC(uint16_t value)
{
    _numberTicketedOTC.fetchAndStoreAcquire(value);
}

uint16_t FunctionControlSr::getNumberTicketedSI() const
{
    return _numberTicketedSI.loadAcquire();
}

void FunctionControlSr::setNumberTicketedSI(uint16_t value)
{
    _numberTicketedSI.fetchAndStoreAcquire(value);
}

uint16_t FunctionControlSr::getIdSI() const
{
    return _idSI.loadAcquire();
}

void FunctionControlSr::setIdSI(uint16_t value)
{
    _idSI.fetchAndStoreAcquire(value);
}

QByteArray FunctionControlSr::serialize()
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);

    qint64 reserve1{0};
    uint32_t reserve2{0};
    uint16_t reserve3{0};

    out << reserve1;
    out << reserve1;
    out << getOffsetTime();
    out << serializeSystemState();
    out << getLiter();
    out << getBandReceiver();
    out << reserve3;
    out << getDoplerCorrection();
    out << getLiterPNS();
    out << getLiterOTC();
    out << serializeDecoders();
    out << getSignalPower();
    out << reserve3;
    out << serializeReadys();

    for(int i = 0; i < 14; ++i)
        out << reserve3;
    out << serializeTicketOtc();
    out << getNumberTicketedOTC();
    out << serializeTicketSi();
    out << getNumberTicketedSI();
    out << getIdSI();
    out << serializeModeTelemetry();
    out << getCounterTelemetry();
    out << reserve1;
    out << reserve2;
    out << reserve3;

    return array;
}

void FunctionControlSr::unserialize(QByteArray &array)
{
    QDataStream in(&array, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_9);
    in.setByteOrder(QDataStream::LittleEndian);

    qint64 reserve1{0};
    uint32_t reserve2{0};
    uint16_t reserve3{0};

    int32_t templateValue;
    int16_t templateValueSigned;
    uint16_t templateValueUnsigned;

    in >> reserve1;
    in >> reserve1;

    in >> templateValue;
    setOffsetTime(templateValue);

    uint16_t systemState{0};
    in >> systemState;
    unserializeSystemState(systemState);

    in >> templateValueUnsigned;
    setLiter(templateValueUnsigned);

    in >> templateValueUnsigned;
    setBandReceiver(templateValueUnsigned);

    in >> reserve3;

    in >> templateValueSigned;
    setDoplerCorrection(templateValueSigned);

    in >> templateValueUnsigned;
    setLiterPNS(templateValueUnsigned);

    in >> templateValueUnsigned;
    setLiterOTC(templateValueUnsigned);

    uint16_t decoders{0};
    in >> decoders;
    unserializeDecoders(decoders);

    in >> templateValueSigned;
    setSignalPower(templateValueSigned);

    in >> reserve3;

    uint16_t readys{0};
    in >> readys;
    unserializeReadies(readys);

    in >> reserve1;
    in >> reserve1;
    in >> reserve1;
    in >> reserve2;

    uint16_t ticketOtc{0};
    in >> ticketOtc;
    unserializeTicketOtc(ticketOtc);
    in >> templateValueUnsigned;
    setNumberTicketedOTC(templateValueUnsigned);

    uint16_t ticketSi{0};
    in >> ticketSi;
    unserializeTicketSi(ticketSi);
    in >> templateValueUnsigned;
    setNumberTicketedSI(templateValueUnsigned);
    in >> templateValueUnsigned;
    setIdSI(templateValueUnsigned);

    uint16_t modeTelemetry{0};
    in >> modeTelemetry;
    unserializeModeTelemetry(modeTelemetry);

    in >> templateValueUnsigned;
    setCounterTelemetry(templateValueUnsigned);
}

void FunctionControlSr::unserialize(StructFunctionControlSr &factoryFormularFccSr)
{
    setOffsetTime(factoryFormularFccSr.offsetTime);
    unserializeSystemState(factoryFormularFccSr.systemState);
    setLiter(factoryFormularFccSr.liter);
    setBandReceiver(factoryFormularFccSr.bandReceiver);
    setLiterPNS(factoryFormularFccSr.literPNS);
    setLiterOTC(factoryFormularFccSr.literOTC);
    unserializeDecoders(factoryFormularFccSr.decoder);
    setSignalPower(factoryFormularFccSr.signalPower);
    unserializeReadies(factoryFormularFccSr.readies);
    unserializeTicketOtc(factoryFormularFccSr.ticketOTC);
    setNumberTicketedOTC(factoryFormularFccSr.numberTicketedOTC);
    unserializeTicketSi(factoryFormularFccSr.ticketSI);
    setNumberTicketedSI(factoryFormularFccSr.numberTicketedSI);
    setIdSI(factoryFormularFccSr.idSI);
    unserializeModeTelemetry(factoryFormularFccSr.modeTLM);
    setCounterTelemetry(factoryFormularFccSr.counterTLM);
}

bool FunctionControlSr::getConnectionState() const
{
    return _connectionState.loadAcquire();
}

void FunctionControlSr::setConnectionState(bool value)
{
    _connectionState.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getWorkModeState() const
{
    return _workModeState.loadAcquire();
}

void FunctionControlSr::setWorkModeState(bool value)
{
    _workModeState.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getImitationPchState() const
{
    return _imitationPchState.loadAcquire();
}

void FunctionControlSr::setImitationPchState(bool value)
{
    _imitationPchState.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getReadyCmosState() const
{
    return _readyCmosState.loadAcquire();
}

void FunctionControlSr::setReadyCmosState(bool value)
{
    _readyCmosState.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getOnPshstate() const
{
    return _onPshstate.loadAcquire();
}

void FunctionControlSr::setOnPshstate(bool value)
{
    _onPshstate.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getArchiveState() const
{
    return _archiveState.loadAcquire();
}

void FunctionControlSr::setArchiveState(bool value)
{
    _archiveState.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getDecoderPk1() const
{
    return _decoderPk1;
}

void FunctionControlSr::setDecoderPk1(bool value)
{
    _decoderPk1.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getDecoderPk2() const
{
    return _decoderPk2;
}

void FunctionControlSr::setDecoderPk2(bool value)
{
    _decoderPk2.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getModulationPch() const
{
    return _modulationPch;
}

void FunctionControlSr::setModulationPch(bool value)
{
    _modulationPch.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getFzsPch() const
{
    return _FzsPch;
}

void FunctionControlSr::setFzsPch(bool value)
{
    _FzsPch.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getConvertatorPch() const
{
    return _convertatorPch;
}

void FunctionControlSr::setConvertatorPch(bool value)
{
    _convertatorPch.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getZeroTicketOtc() const
{
    return _zeroTicketOtc;
}

void FunctionControlSr::setZeroTicketOtc(bool value)
{
    _zeroTicketOtc.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getPlusTicketOtc() const
{
    return _plusTicketOtc;
}

void FunctionControlSr::setPlusTicketOtc(bool value)
{
    _plusTicketOtc.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getProcessTicketOtc() const
{
    return _processTicketOtc;
}

void FunctionControlSr::setProcessTicketOtc(bool value)
{
    _processTicketOtc.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getZeroTicketSi() const
{
    return _zeroTicketSi;
}

void FunctionControlSr::setZeroTicketSi(bool value)
{
    _zeroTicketSi.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getMinusTicketSi() const
{
    return _minusTicketSi;
}

void FunctionControlSr::setMinusTicketSi(bool value)
{
    _minusTicketSi.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getPlusTicketSi() const
{
    return _plusTicketSi;
}

void FunctionControlSr::setPlusTicketSi(bool value)
{
    _plusTicketSi.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getProcessTicketSi() const
{
    return _processTicketSi;
}

void FunctionControlSr::setProcessTicketSi(bool value)
{
    _processTicketSi.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getOnTicketSi() const
{
    return _onTicketSi;
}

void FunctionControlSr::setOnTicketSi(bool value)
{
    _onTicketSi.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getOneModeTelemetry() const
{
    return _oneModeTelemetry;
}

void FunctionControlSr::setOneModeTelemetry(bool value)
{
    _oneModeTelemetry.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getEightModeTelemetry() const
{
    return _eightModeTelemetry;
}

void FunctionControlSr::setEightModeTelemetry(bool value)
{
    _eightModeTelemetry.fetchAndStoreAcquire(value);
}

bool FunctionControlSr::getThirtyTwoTicketSi() const
{
    return _thirtyTwoTicketSi;
}

void FunctionControlSr::setThirtyTwoTicketSi(bool value)
{
    _thirtyTwoTicketSi.fetchAndStoreAcquire(value);
}

void FunctionControlSr::unserializeSystemState(const uint16_t systemState)
{
    setConnectionState(BitUtils::getValueByBitInbex(systemState));
    setWorkModeState(BitUtils::getValueByBitInbex(systemState, 2));
    setImitationPchState(BitUtils::getValueByBitInbex(systemState, 4));
    setReadyCmosState(BitUtils::getValueByBitInbex(systemState, 8));
    setOnPshstate(BitUtils::getValueByBitInbex(systemState, 10));
    setArchiveState(BitUtils::getValueByBitInbex(systemState, 14));
}

void FunctionControlSr::unserializeDecoders(const uint16_t decoders)
{
    setDecoderPk1(BitUtils::getValueByBitInbex(decoders));
    setDecoderPk2(BitUtils::getValueByBitInbex(decoders, 1));
}

void FunctionControlSr::unserializeReadies(const uint16_t readys)
{
    setModulationPch(BitUtils::getValueByBitInbex(readys));
    setFzsPch(BitUtils::getValueByBitInbex(readys, 1));
    setConvertatorPch(BitUtils::getValueByBitInbex(readys, 2));
}

void FunctionControlSr::unserializeTicketOtc(const uint16_t ticketOtc)
{
    setZeroTicketOtc(BitUtils::getValueByBitInbex(ticketOtc));
    setPlusTicketOtc(BitUtils::getValueByBitInbex(ticketOtc, 1));
    setProcessTicketOtc(BitUtils::getValueByBitInbex(ticketOtc, 2));
}

void FunctionControlSr::unserializeTicketSi(const uint16_t ticketSi)
{
    setZeroTicketSi(BitUtils::getValueByBitInbex(ticketSi));
    setMinusTicketSi(BitUtils::getValueByBitInbex(ticketSi, 1));
    setPlusTicketSi(BitUtils::getValueByBitInbex(ticketSi, 2));
    setProcessTicketSi(BitUtils::getValueByBitInbex(ticketSi, 3));
    setOnTicketSi(BitUtils::getValueByBitInbex(ticketSi, 5));
}

void FunctionControlSr::unserializeModeTelemetry(const uint16_t modeTelemetry)
{
    setOneModeTelemetry(BitUtils::getValueByBitInbex(modeTelemetry));
    setEightModeTelemetry(BitUtils::getValueByBitInbex(modeTelemetry, 1));
    setThirtyTwoTicketSi(BitUtils::getValueByBitInbex(modeTelemetry, 2));
}

uint16_t FunctionControlSr::serializeSystemState()
{
    uint16_t systemState{0};
    BitUtils::setValueByBitInbex(systemState, 0, getConnectionState());
    BitUtils::setValueByBitInbex(systemState, 2, getWorkModeState());
    BitUtils::setValueByBitInbex(systemState, 4, getImitationPchState());
    BitUtils::setValueByBitInbex(systemState, 8, getReadyCmosState());
    BitUtils::setValueByBitInbex(systemState, 10, getOnPshstate());
    BitUtils::setValueByBitInbex(systemState, 14, getArchiveState());

    return systemState;
}

uint16_t FunctionControlSr::serializeDecoders() const
{
    uint16_t decoders{0};

    BitUtils::setValueByBitInbex(decoders, 0, getDecoderPk1());
    BitUtils::setValueByBitInbex(decoders, 1, getDecoderPk2());

    return decoders;
}

uint16_t FunctionControlSr::serializeReadys() const
{
    uint16_t readys{0};

    BitUtils::setValueByBitInbex(readys, 0, getModulationPch());
    BitUtils::setValueByBitInbex(readys, 1, getFzsPch());
    BitUtils::setValueByBitInbex(readys, 2, getConvertatorPch());

    return readys;
}

uint16_t FunctionControlSr::serializeTicketOtc() const
{
    uint16_t ticketOtc{0};

    BitUtils::setValueByBitInbex(ticketOtc, 0, getZeroTicketOtc());
    BitUtils::setValueByBitInbex(ticketOtc, 1, getPlusTicketOtc());
    BitUtils::setValueByBitInbex(ticketOtc, 2, getProcessTicketOtc());

    return ticketOtc;
}

uint16_t FunctionControlSr::serializeTicketSi() const
{
    uint16_t ticketSi{0};

    BitUtils::setValueByBitInbex(ticketSi, 0, getZeroTicketSi());
    BitUtils::setValueByBitInbex(ticketSi, 1, getMinusTicketSi());
    BitUtils::setValueByBitInbex(ticketSi, 2, getPlusTicketSi());
    BitUtils::setValueByBitInbex(ticketSi, 3, getProcessTicketSi());
    BitUtils::setValueByBitInbex(ticketSi, 5, getOnTicketSi());

    return ticketSi;
}

uint16_t FunctionControlSr::serializeModeTelemetry() const
{
    uint16_t modeTlm{0};

    BitUtils::setValueByBitInbex(modeTlm, 0, getOneModeTelemetry());
    BitUtils::setValueByBitInbex(modeTlm, 1, getEightModeTelemetry());
    BitUtils::setValueByBitInbex(modeTlm, 2, getThirtyTwoTicketSi());

    return modeTlm;
}

