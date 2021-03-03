#include "linkingFcc/Parser/ParserModem.h"

ParserModem::ParserModem(QSharedPointer<IJournal> journal,
                         SenderParamsStation *sender)
    : BaseParser(journal, sender)
{

}

void ParserModem::parseParams(const QJsonObject& obj)
{
    //params.getInfoFC()->setIdSI(params.getSpecialInfo().idSI());

    /// Текущее время ЗС(Posix)
    QJsonValue jv = obj.value("s_code");
    uint64_t currentTime{0};
    if(!jv.isUndefined())
    {
        currentTime = jv.toInt();
        params.getInfoFC()->getRefInfoControl()->setCurrentTime(currentTime);

        _journal->setTime(currentTime);
    }

    double levelCorrection{0.0};
    jv = obj.value("correctionLevel");
    if(!jv.isUndefined())
        levelCorrection = jv.toDouble();

    double correctAdjustment{0.0};
    jv = obj.value("correctAdjustment");
    if(!jv.isUndefined())
        correctAdjustment = jv.toDouble();

    jv = obj.value("dpll_ctrl.band");
    if(!jv.isUndefined()) {
        int index = jv.toInt();
        int array[] = {
            125,
            250,
            500,
            1000,
            2000,
            4000,
            8000,
            16000,
            0,
            0
        };
        params.getInfoFC()->getRefInfoControl()->setBandReceiver(array[index]);
    }

    /// Оцифровка времени НАП (Posix)
    if(_napTime != jv.toInt() && _napTime > 0) {
        params.getInfoFC()->getRefInfoControl()->setSwap((uint8_t)Swap::NP, true);
    }
    jv = obj.value("irig_b_time");
    if(!jv.isUndefined()) {
        _napTime = jv.toInt();
        params.getInfoFC()->getRefInfoControl()->setDigitizationTime(jv.toInt());
    }

    /// Расхождение между секундными метками оцифровки времени НАП и текущего времени
    jv = obj.value("time_difference");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setOffsetTime(jv.toInt());

    /// Захват несущей
    jv = obj.value("reciver_status.dpll_locker");
    if(!jv.isUndefined())
    {
        auto ticket = jv.toBool();
        params.getInfoFC()->setSystemState(SystemState::LOCK_CARRIER, ticket);
        params.setLockAnswer(ticket);
    }

    /// Захват ПШС
    jv = obj.value("reciver_status.pn_dpll_locked");
    if(!jv.isUndefined())
        params.getInfoFC()->setSystemState(SystemState::LOCK_PNS, jv.toBool());

    /// Литер РК
    jv = obj.value("modulation_ctrl.emitting");
    if(!jv.isUndefined()) {
        params.getInfoFC()->setSystemState(SystemState::MODEM_RADIATION, jv.toBool());
        params.getInfoFC()->setSystemState(SystemState::RADIATION_AMPLIFIER_1, jv.toBool());
    }

    jv = obj.value("symbolSingleCmd");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setLiterOTC(jv.toInt());

    /// Литер ПШС
    jv = obj.value("rec_pn_m2");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setLiterPNS(jv.toInt());

    /// Полоса ПРМ
   /* jv = obj.value("dpll_ctrl.band");
    if(!jv.isUndefined())
        params.getInfoFC()->setBandReceiver(jv.toInt());*/

    /// Поисковая поправка
    jv = obj.value("searchCorrectionRequest");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setSearchCorrection(jv.toInt() / 10);

    /// Доплеровская поправка
    jv = obj.value("dopplerCorrectionRequest");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setDoplerCorrection(jv.toInt() / 10);

    /// Уровень сигнала на входе МШУ, пересчитанный со входа модема Т-Б, в ДбВт
    jv = obj.value("signal_power");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setSignalPower(jv.toInt() + levelCorrection);

    /// Ключ СКЗИ
    jv = obj.value("CISTKey");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setKeySCPI(jv.toInt());

    /// Ключ БСК
    jv = obj.value("onboardSessionKey");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setKeyOSK(jv.toInt());

    /// режим компенсации
    jv = obj.value("correction_mode");
    int modeDopler{0};
    if(!jv.isUndefined())
        modeDopler = jv.toInt();

    /// Счётчик кадров ТЛМ
    jv = obj.value("cntTMIFrame");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setCounterTLM(jv.toInt());

    bool isPNModeOFF{true};
    /// ПШС
    jv = obj.value("modulation_ctrl.pn_mode");
    if(!jv.isUndefined())
        isPNModeOFF &= jv.toInt() == 0;

    /// ПШС
    jv = obj.value("pn_demod_ctrl.pn_mode");
    if(!jv.isUndefined())
        isPNModeOFF &= jv.toInt() == 0;

    params.getInfoFC()->setSystemState(SystemState::MODULATION_PNS, !isPNModeOFF);

    /// Отклонение частоты
    jv = obj.value("deviationFreq");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setFrequencyDeviation(jv.toInt() / 10);

    /// Наличие ЦУ
    jv = obj.value("isLoadTargetDesignationInfo");
    if(!jv.isUndefined())
    {
        bool isTD = jv.toBool();
        params.setIsModemTD(isTD);
        params.getInfoFC()->setModeORM(ModeORM::ID_ORM, isTD);
    }

    jv = obj.value("isLoadTargetDesignationInfoDoppler");
    if(!jv.isUndefined())
    {
        bool isTD = jv.toBool();
        params.setIdCU(isTD);
        params.getInfoFC()->setModeORM(ModeORM::ID_DOPLER, isTD);
    }

    /// Темп измерений РКО
    jv = obj.value("measurementRate");
    if(!jv.isUndefined())
    {
        int mr = jv.toInt();
        params.getInfoFC()->resetTempMeasurementORM();
        ModeORM mode{ModeORM::SEC_1};
        if(mr == 1 || mr == 10)
            mode = ModeORM::SEC_10;
        else if(mr == 2 || mr == 20)
            mode = ModeORM::SEC_20;
        params.getInfoFC()->setModeORM(mode, true);
    }

    /// Количество измерений РКО
    jv = obj.value("measurementNumber");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setCounterDistance(jv.toInt());

    /// Изм. ДЗ
    bool enableORM{false};
    jv = obj.value("enableORM");
    if(!jv.isUndefined())
    {
        enableORM = jv.toBool();
        params.getInfoFC()->setModeORM(ModeORM::CHANGE_DISTANCE, enableORM);
    }

    if(enableORM)
    {
        if(_startTime == 0)
            _startTime = params.getInfoFC()->getRefInfoControl()->getCurrentTime();

        /// Номер измерения
        int32_t numMeasurement{0};
        jv = obj.value("currentNumMeasurement");

        if(!jv.isUndefined())
            numMeasurement = jv.toInt();

        params.getInfoFC()->getRefInfoControl()->setCounterDistance(numMeasurement);

        /// Измеренная дальность
        double currentDistance{-1};
        jv = obj.value("currentDistance");
        if(!jv.isUndefined())
            currentDistance = jv.toDouble();

        qint64 currentDistanceTime{-1};
        jv = obj.value("currentDistanceTime");
        if(!jv.isUndefined())
            currentDistanceTime = (qint64)jv.toInt();

        double currentDelay = 0;
        jv = obj.value("currentDelay");
        if(!jv.isUndefined())
            currentDelay = jv.toDouble();

        if(_currentInterval != numMeasurement && numMeasurement > 0)
        {
            _distances.push_back(currentDistance);
            _times.push_back(currentDistanceTime);
            _currentInterval = numMeasurement;

            QString message = QString("%1: %2 км (%3 %4нс)")
                    .arg(numMeasurement)
                    .arg(QString::number(currentDistance / 1000.0, 'f', 5))
                    .arg(QDateTime::fromMSecsSinceEpoch(currentDistanceTime * 1000).toOffsetFromUtc(3 * 60 * 60).toString("dd.MM.yyyy hh:mm:ss"))
                    .arg(uint32_t(currentDelay * 1e9));
            _journal->writeEvent(message);
        }
    }
    else {
        writeParamsORM(0);
        _startTime = 0;
        _currentInterval = 0;
    }

    /// ПК 2
    jv = obj.value("isSecondPreamble");
    if(!jv.isUndefined())
    {
        params.getInfoFC()->getRefInfoControl()->setDecoder(OnboardDecoder::HS2, jv.toBool());
        params.getInfoFC()->getRefInfoControl()->setDecoder(OnboardDecoder::HS1, !jv.toBool());
    }

    /// Доплер несущей
    jv = obj.value("doppler_carrier_freq");
    double dopplerCarrier{0.};
    if(!jv.isUndefined())
        dopplerCarrier = jv.toDouble();

    /// Доплер ПШС
    jv = obj.value("doppler_carrier_pn_freq");
    double dopplerPN{0.};
    if(!jv.isUndefined())
        dopplerPN = jv.toDouble();

    /// Подключение к БСУ
    jv = obj.value("CLUConectedState");
    if(!jv.isUndefined()) {
        params.getInfoFC()->setSwap(Swap::LIU, jv.toBool());
        params.getInfoFC()->setSystemState(SystemState::MODE_CLOSE, jv.toBool());
    }

    bool isEnabledDopplerCorrection = false;
    jv = obj.value("enabledDopplerCorrection");
    if(!jv.isUndefined())
        isEnabledDopplerCorrection = jv.toBool();

    /// Компенсация доплера
    jv = obj.value("dopplerPNCorrection");
    if(!jv.isUndefined())
        params.setDopplerPNCorrection(jv.toDouble());

    if(isEnabledDopplerCorrection)
    {
        if(modeDopler == 0)
        {
            params.getInfoFC()->setSystemState(SystemState::DOPLER_COMPLECT_TD, true);
            params.getInfoFC()->setSystemState(SystemState::DOPLER_COMPLECT_ANSWER, false);
            params.setDoplerTimeTD(currentTime);
            params.setCompensationCarrierTD(dopplerCarrier);
            params.setCompensationPNSTD(params.getDopplerPNCorrection());
            params.getInfoFC()->getRefInfoControl()->setDopplerFreqPrediction(dopplerCarrier / 10);
        }

        if(modeDopler == 1)
        {
            params.getInfoFC()->setSystemState(SystemState::DOPLER_COMPLECT_TD, false);
            params.getInfoFC()->setSystemState(SystemState::DOPLER_COMPLECT_ANSWER, true);
            params.setDoplerTimeAnswer(currentTime);
            params.setCompensationCarrierAnswer(dopplerCarrier);
            params.setCompensationPNSAnswer(params.getDopplerPNCorrection());
            params.getInfoFC()->getRefInfoControl()->setDopplerFreqPrediction(dopplerCarrier / 10);
        }
    }
    else
    {
        params.getInfoFC()->setSystemState(SystemState::DOPLER_COMPLECT_TD, false);
        params.getInfoFC()->setSystemState(SystemState::DOPLER_COMPLECT_ANSWER, false);
        params.setDoplerTimeTD(0);
        params.setCompensationCarrierTD(0);
        params.setCompensationPNSTD(0);
        params.setDoplerTimeAnswer(0);
        params.setCompensationCarrierAnswer(0);
        params.setCompensationPNSAnswer(0);
        params.getInfoFC()->getRefInfoControl()->setDopplerFreqPrediction(0);
    }
}

void ParserModem::writeParamsORM(const int64_t d)
{
    if(_distances.isEmpty()) return;

    //QFile fl("distance.txt");
    //fl.open(QIODevice::WriteOnly);

    QString kaString = QString("%1").arg(params.getNumberKA(), 4, 10, QChar('0'));
    QString vitkaString = QString("%1").arg(params.getNumberVitok(), 5, 10, QChar('0'));
    QString seansaString = QString("%1").arg(params.getNumberSeans(), 2, 10, QChar('0'));

    QString fileName = kaString + separator + vitkaString + separator + seansaString + expansion;

    int rate = params.getInfoFC()->getModeORM(ModeORM::SEC_1) ? 1 : params.getInfoFC()->getModeORM(ModeORM::SEC_10) ? 10 : 20;
    QByteArray rko;
    for(int i = 0; i < _distances.size(); ++i) {

        quint64 inttime = _times[i];//_startTime + (i * rate);//params.getInfoFC().getCurrentTime();

        //QString dt = QString("%1 %2\n").arg(_distances[i]).arg(QDateTime::fromMSecsSinceEpoch(inttime * 1000).toOffsetFromUtc(3 * 60 * 60).toString("dd.MM.yyyy hh:mm:ss"));
        //fl.write(dt.toStdString().c_str(), dt.toStdString().size());

        double stupidTime = QDateTime::fromMSecsSinceEpoch(inttime * 1000).toOffsetFromUtc(3 * 60 * 60).time().msecsSinceStartOfDay()/1000.0;
        if(stupidTime < 4.5) {
            stupidTime += 86400.0;
        }
        inttime = std::round(stupidTime*2);
        inttime <<= 16;

        quint64 cms = std::round(_distances[i]*100);

        quint32 dword0 = inttime >> 4;
        quint8 byte1 = inttime >> 20;
        quint8 byte2 = inttime >> 28;
        quint8 byte3 = inttime >> 4;
        quint8 byte4 = inttime >> 12;
        quint8 byte5 = cms >> 24;
        quint8 byte6 = (cms >> 32) | (inttime << 4);
        quint8 byte7 = cms >> 8;
        quint8 byte8 = cms >> 16;
        quint8 byte9 = (0b0010) << 4;
        quint8 byte10 = cms;

        rko.append(byte1);
        rko.append(byte2);
        rko.append(byte3);
        rko.append(byte4);
        rko.append(byte5);
        rko.append(byte6);
        rko.append(byte7);
        rko.append(byte8);
        rko.append(byte9);
        rko.append(byte10);
    }

    //fl.close();

    _distances.clear();
    _times.clear();

    FileWorkerORM worker(TypeFileORM::DISTANCE);
    worker.setNameFile(fileName);
    if(worker.write(rko))
        qDebug() << "success record RCO";
}
