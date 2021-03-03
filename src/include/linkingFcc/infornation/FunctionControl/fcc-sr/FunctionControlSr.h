#ifndef FUNCTIONCONTROL_H
#define FUNCTIONCONTROL_H

#include <stdint.h>
#include <QMutexLocker>
#include <QDataStream>
#include <qatomic.h>

#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/StructFunctionControlSr.h"

class FunctionControlSr
{
    QAtomicInteger<int32_t> _offsetTime;                 ///< Расхождение между секундными метками оцифровки времени НРТК и текущего времени в микросекундах (LongInt), цена младшего разряда 1 мкс
    QAtomicInteger<uint16_t> _liter{0};                  ///< Литер несущей (Word)
    QAtomicInteger<uint16_t> _bandReceiver{0};           ///< Полоса приемника, Гц (Word)
    QAtomicInteger<int16_t> _doplerCorrection{0};        ///< Доплеровское смещение (Integer), цена мл. разряда 10 Гц (прогноз по ответному сигналу)
    QAtomicInteger<uint16_t> _literPNS{0};               ///< Литер ПШС (Word)
    QAtomicInteger<uint16_t> _literOTC{0};               ///< Литер РК (Word)
    QAtomicInteger<int16_t> _signalPower{0};             ///< Уровень сигнала
    QAtomicInteger<uint16_t> _numberTicketedOTC{0};      ///< Номер квитируемой РК(ОРК) (Word)
    QAtomicInteger<uint16_t> _numberTicketedSI{0};       ///< Номер квитируемой фразы СИ (Word)
    QAtomicInteger<uint16_t> _idSI{0};                   ///< Идентификатор СИ (копируется из заголовка СИ)
    QAtomicInteger<uint16_t> _counterTelemetry{0};       ///< Счетчик кадров ТЛМ

    uint16_t reserve{0};                ///< Резервное слово

    // Состояние системы
    QAtomicInteger<uint8_t> _connectionState;        ///< Состояние составляющего системы "Связь"
    QAtomicInteger<uint8_t> _workModeState;          ///< Состояние составляющего системы "Работа"
    QAtomicInteger<uint8_t> _imitationPchState;      ///< Состояние составляющего системы "Имитация ПЧ"
    QAtomicInteger<uint8_t> _readyCmosState;         ///< Состояние составляющего системы "Готовность ЦМОС"
    QAtomicInteger<uint8_t> _onPshstate;             ///< Состояние составляющего системы "Состояние ПШС"
    QAtomicInteger<uint8_t> _archiveState;           ///< Состояние составляющего системы "Архив"

    // Выбор бортовых дешифраторов
    QAtomicInteger<uint8_t> _decoderPk1;             ///< ПК1 РК
    QAtomicInteger<uint8_t> _decoderPk2;             ///< ПК2 РК

    // Готовность
    QAtomicInteger<uint8_t> _modulationPch;          ///< Мод. ПЧ
    QAtomicInteger<uint8_t> _FzsPch;                 ///< ФЗС ПЧ
    QAtomicInteger<uint8_t> _convertatorPch;         ///< Конв. ПЧ

    // Квитанция РК
    QAtomicInteger<uint8_t> _zeroTicketOtc;         ///< 0 кв
    QAtomicInteger<uint8_t> _plusTicketOtc;         ///< +КВ
    QAtomicInteger<uint8_t> _processTicketOtc;      ///< Идет

    // Квитанция СИ
    QAtomicInteger<uint8_t> _zeroTicketSi;         ///< 0 кв
    QAtomicInteger<uint8_t> _minusTicketSi;        ///< -КВ
    QAtomicInteger<uint8_t> _plusTicketSi;         ///< +КВ
    QAtomicInteger<uint8_t> _processTicketSi;      ///< Идет
    QAtomicInteger<uint8_t> _onTicketSi;           ///< Вкл СИ

    // Режим ТЛМ
    QAtomicInteger<uint8_t> _oneModeTelemetry;     ///< ТЛМ 1 кГц
    QAtomicInteger<uint8_t> _eightModeTelemetry;   ///< ТЛМ 8 кГц
    QAtomicInteger<uint8_t> _thirtyTwoTicketSi;    ///< ТЛМ 32 кГц

    void unserializeSystemState(const uint16_t systemState);
    void unserializeDecoders(const uint16_t decoders);
    void unserializeReadies(const uint16_t readys);
    void unserializeTicketOtc(const uint16_t ticketOtc);
    void unserializeTicketSi(const uint16_t ticketSi);
    void unserializeModeTelemetry(const uint16_t modeTelemetry);

    uint16_t serializeSystemState();
    uint16_t serializeDecoders() const;
    uint16_t serializeReadys() const;
    uint16_t serializeTicketOtc() const;
    uint16_t serializeTicketSi() const;
    uint16_t serializeModeTelemetry() const;

public:
    FunctionControlSr() {}
    ~FunctionControlSr() {}

    ///< Расхождение между секундными метками оцифровки времени НРТК и текущего времени в микросекундах (LongInt), цена младшего разряда 1 мкс
    int32_t getOffsetTime() const;
    void setOffsetTime(int32_t value);

    ///< Литер несущей (Word)
    uint16_t getLiter() const;
    void setLiter(uint16_t value);

    ///< Полоса приемника, Гц (Word)
    uint16_t getBandReceiver() const;
    void setBandReceiver(uint16_t value);

    ///< Доплеровское смещение (Integer), цена мл. разряда 10 Гц (прогноз по ответному сигналу)
    int16_t getDoplerCorrection() const;
    void setDoplerCorrection(int16_t value);

    ///< Литер ПШС (Word)
    uint16_t getLiterPNS() const;
    void setLiterPNS(uint16_t value);

    ///< Литер РК (Word)
    uint16_t getLiterOTC() const;
    void setLiterOTC(uint16_t value);

    ///< Уровень сигнала
    int16_t getSignalPower() const;
    void setSignalPower(int16_t value);

    ///< Номер квитируемой РК(ОРК) (Word)
    uint16_t getNumberTicketedOTC() const;
    void setNumberTicketedOTC(uint16_t value);

    ///< Номер квитируемой фразы СИ (Word)
    uint16_t getNumberTicketedSI() const;
    void setNumberTicketedSI(uint16_t value);

    ///< Идентификатор СИ (копируется из заголовка СИ)
    uint16_t getIdSI() const;
    void setIdSI(uint16_t value);

    ///< Счетчик кадров ТЛМ
    uint16_t getCounterTelemetry() const;
    void setCounterTelemetry(uint16_t value);

    // Состояние системы
    bool getConnectionState() const;
    void setConnectionState(bool value);
    bool getWorkModeState() const;
    void setWorkModeState(bool value);
    bool getImitationPchState() const;
    void setImitationPchState(bool value);
    bool getReadyCmosState() const;
    void setReadyCmosState(bool value);
    bool getOnPshstate() const;
    void setOnPshstate(bool value);
    bool getArchiveState() const;
    void setArchiveState(bool value);

    // Выбор бортовых дешифраторов
    bool getDecoderPk1() const;
    void setDecoderPk1(bool value);
    bool getDecoderPk2() const;
    void setDecoderPk2(bool value);

    // Готовность
    bool getModulationPch() const;
    void setModulationPch(bool value);
    bool getFzsPch() const;
    void setFzsPch(bool value);
    bool getConvertatorPch() const;
    void setConvertatorPch(bool value);

    // Квитанция РК
    bool getZeroTicketOtc() const;
    void setZeroTicketOtc(bool value);
    bool getPlusTicketOtc() const;
    void setPlusTicketOtc(bool value);
    bool getProcessTicketOtc() const;
    void setProcessTicketOtc(bool value);

    // Квитанция СИ
    bool getZeroTicketSi() const;
    void setZeroTicketSi(bool value);
    bool getMinusTicketSi() const;
    void setMinusTicketSi(bool value);
    bool getPlusTicketSi() const;
    void setPlusTicketSi(bool value);
    bool getProcessTicketSi() const;
    void setProcessTicketSi(bool value);
    bool getOnTicketSi() const;
    void setOnTicketSi(bool value);

    // Режим ТЛМ
    bool getOneModeTelemetry() const;
    void setOneModeTelemetry(bool value);
    bool getEightModeTelemetry() const;
    void setEightModeTelemetry(bool value);
    bool getThirtyTwoTicketSi() const;
    void setThirtyTwoTicketSi(bool value);

    QByteArray serialize();
    void unserialize(QByteArray &array);
    void unserialize(StructFunctionControlSr &factoryFormularFccSr);
};

#endif // FUNCTIONCONTROL_H
