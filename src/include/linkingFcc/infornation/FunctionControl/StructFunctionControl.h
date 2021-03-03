#ifndef STRUCTFUNCTIONCONTROL_H
#define STRUCTFUNCTIONCONTROL_H

#include <stdint.h>
#include <QMutexLocker>

#include "EnumsFunctionControl.h"
#include "utils/Degree.h"

class StructFunctionControl
{
    uint64_t currentTime{0};            ///< Текущее время ЗС(Posix)из модема
    uint64_t digitizationTime{0};       ///< Оцифровка времени НАП (Posix) с НП1
    int32_t offsetTime{0};              ///< Расхождение между секундными метками оцифровки времени НАП и текущего времени в микросекундах (LongInt), цена младшего разряда 1 мкс из модема
    uint16_t liter{1};                  ///< Литер несущей (Word)
    uint16_t bandReceiver{0};           ///< Полоса приемника, Гц (Word)
    int16_t searchCorrection{0};        ///< Поисковая поправка (Integer)
    int16_t doplerCorrection{0};        ///< Доплеровская поправка (Integer)
    uint16_t literPNS{0};               ///< Литер ПШС (Word)
    uint16_t literOTC{0};               ///< Литер РК (Word)
    uint16_t decoder{1};                ///< Выбор бортовых дешифраторов (Word) , выбор –1 в соответствующем разряде
    int16_t signalPower{0};             ///< Уровень сигнала на входе МШУ, пересчитанный со входа модема Т-Б, в ДбВт
    double azimuthFBS{0.};              ///< ДОС азимут (Integer), цена младшего разряда 10”U+0020
    double elevationFBS{0.};            ///< ДОС угол места (Word), цена младшего разряда 10”
    double correctionAzimuth{0.};       ///< Поправка по азимуту (Smallint), цена младшего разряда 10”
    double correctionElevation{0.};     ///< Поправка по углу места (Smallint), цена младшего разряда 10”
    double pointAzimuth{0.};            ///< Точка азимута к которой движется антенна (Integer), цена младшего разряда 10”
    double pointElevation{0.};          ///< Точка угла места к которой движется антенна (Integer), цена младшего разряда 10”
    uint16_t keySCPI{0};                ///< Ключ СКЗИ
    uint16_t keyOSK{0};                 ///< Ключ БСК (бортовой сеансный ключ)
    uint16_t word33{0};                 ///< 649 - положение переключателей, 711 - давление, 512 - резерв
    uint16_t reserve_2{0};              ///< 711 - Влажность(8) + Температура(8)
    uint16_t reserve_3{0};              ///< 711 - Скорость ветра(7) + Направление ветра(9)
    uint16_t ticketOTC{0};              ///< Квитанция РК (Word) , тип квитанции -1 в соответствующем разряде
    uint16_t numberTicketedOTC{0};      ///< Номер квитируемой РК(ОРК) (Word)
    uint16_t ticketSI{0};               ///< Квитанция СИ (Word) , тип квитанции и состояние -1 в соответствующем разряде
    uint16_t numberTicketedSI{0};       ///< Номер квитируемой фразы СИ (Word)
    uint16_t idSI{0};                   ///< Идентификатор СИ (копируется из заголовка СИ)
    uint16_t modeTLM{0};                ///< Режим ТЛМ (Word) , режим -1 в соответствующем разряде
    uint16_t counterTLM{0};             ///< Счетчик кадров ТЛМ (Word)
    uint16_t modeORM{0};                ///< Режим РКО (Word) , режим -1 в соответствующем разряде
    uint16_t counterAngle{0};           ///< Счетчик угловых измерений
    uint16_t counterDistance{0};        ///< Счетчик измерений дальности
    int16_t dopplerFreqPrediction{0};   ///< Прогноз компенсации частоты доплера (Word), цена младшего разряда 10 Гц
    int16_t frequencyDeviation{0};      ///< Отклонение частоты (Word), цена младшего разряда 10 Гц
    uint16_t alarmDevice{0};            ///< Авария устройства (Word) , авария - 1 в соответствующем разряде
    uint16_t powerReceiver{0};          ///< Мощность передатчика (Word), в Ваттах
    uint16_t attenuator{0};             ///< Аттенюатор передатчика (Word), цена младшего разряда 0,1Дб
    int16_t tempReceiver{0};            ///< Температура передатчика (Word), в гр. С
    uint16_t systemState{0};            ///< Состояние системы (Word) , наличие режима -1 в соответствующем разряде
    uint16_t complects{0};              ///< Комплекты (Word) , 0 - 1-ый комплект, 1 - 2-ой комплект
    uint16_t swap{0};                   ///< Наличие обмена (Word) , обмен с устройством -1 в соответствующем разряде
    int16_t modeANT{0};                 ///< Режим АНТ (Word) , наличие режима -1 в соответствующем разряде, при программном или ручном режиме указывается наличие типа поправки

    mutable QMutex _mutex;              ///< Мьютекс для синхронизации доступа к полям

public:
    StructFunctionControl();
    StructFunctionControl(const StructFunctionControl& control);
    StructFunctionControl &operator=(const StructFunctionControl& control);

    ///< Текущее время ЗС(Posix)из модема
    uint64_t getCurrentTime() const;
    void setCurrentTime(const uint64_t &value);

    ///< Оцифровка времени НАП (Posix) с НП1
    uint64_t getDigitizationTime() const;
    void setDigitizationTime(const uint64_t &value);

    ///< Расхождение между секундными метками оцифровки времени НАП и текущего времени в микросекундах (LongInt), цена младшего разряда 1 мкс из модема
    int32_t getOffsetTime() const;
    void setOffsetTime(const int32_t &value);

    ///< Литер несущей (Word)
    uint16_t getLiter() const;
    void setLiter(const uint16_t &value);

    ///< Полоса приемника, Гц (Word)
    uint16_t getBandReceiver() const;
    void setBandReceiver(const uint16_t &value);

    ///< Поисковая поправка (Integer)
    int16_t getSearchCorrection() const;
    void setSearchCorrection(const int16_t &value);

    ///< Доплеровская поправка (Integer)
    int16_t getDoplerCorrection() const;
    void setDoplerCorrection(const int16_t &value);

    ///< Литер ПШС (Word)
    uint16_t getLiterPNS() const;
    void setLiterPNS(const uint16_t &value);

    // Литер РК (Word)
    uint16_t getLiterOTC() const;
    void setLiterOTC(const uint16_t &value);

    ///< Выбор бортовых дешифраторов (Word) , выбор –1 в соответствующем разряде
    bool getDecoder(const OnboardDecoder numDecoder) const;
    uint16_t getDecoder() const;
    void setDecoder(OnboardDecoder numDecoder, bool state);

    ///< Уровень сигнала на входе МШУ, пересчитанный со входа модема Т-Б, в ДбВт
    int16_t getSignalPower() const;
    void setSignalPower(const int16_t &value);

    ///< ДОС азимут (Integer), цена младшего разряда 10”U+0020
    double getAzimuthFBS() const;
    QString getStringAzimuthFBS() const;
    void setAzimuthFBS(const double &value);

    ///< ДОС угол места (Word), цена младшего разряда 10”
    double getElevationFBS() const;
    QString getStringElevationFBS() const;
    void setElevationFBS(const double &value);

    ///< Поправка по азимуту (Smallint), цена младшего разряда 10”
    double getCorrectionAzimuth() const;
    void setCorrectionAzimuth(const double &value);
    QString getStringCorrectionAzimuth() const;

    ///< Поправка по углу места (Smallint), цена младшего разряда 10”
    double getCorrectionElevation() const;
    void setCorrectionElevation(const double &value);
    QString getStringCorrectionElevation() const;

    ///< Точка азимута к которой движется антенна (Integer), цена младшего разряда 10”
    double getPointAzimuth() const;
    void setPointAzimuth(const double &value);

    ///< Точка угла места к которой движется антенна (Integer), цена младшего разряда 10”
    double getPointElevation() const;
    void setPointElevation(const double &value);

    ///< Ключ СКЗИ
    uint16_t getKeySCPI() const;
    void setKeySCPI(const uint16_t &value);

    ///< Ключ БСК (бортовой сеансный ключ)
    uint16_t getKeyOSK() const;
    void setKeyOSK(const uint16_t &value);

    ///< Положение переключателей
    uint16_t getWord33() const;
    uint16_t getSwitch(const Switches &value) const;
    void setSwitch(const Switches &value, const bool state);
    void setWord33(const uint16_t state);

    ///< резерв
    uint16_t getWord34() const;
    void setWord34(const uint16_t &value);
    uint8_t getTemp() const;
    void setTemp(const int8_t temp);
    uint8_t getHumidity() const;
    void setHumidity(const uint8_t humidity);

    ///< резерв
    uint16_t getWord35() const;
    void setWord35(const uint16_t &value);
    uint8_t getWindSpeed() const;
    void setWindSpeed(const uint8_t &value);
    uint16_t getWindDirection() const;
    void setWindDirection(const uint16_t &value);

    ///< Квитанция РК (Word) , тип квитанции -1 в соответствующем разряде
    bool getTicketOTC(const TicketOTC ticket) const;
    uint16_t getTicketOTC() const;
    void setTicketOTC(const TicketOTC ticket, const bool state);
    void setTicketOTCFaultCounter(uint8_t value);

    ///< Номер квитируемой РК(ОРК) (Word)
    uint16_t getNumberTicketedOTC() const;
    void setNumberTicketedOTC(const uint16_t &value);

    ///< Квитанция СИ (Word) , тип квитанции и состояние -1 в соответствующем разряде
    bool getTicketSI(const TicketSI ticket) const;
    uint16_t getTicketSI() const;
    void setTicketSI(const TicketSI ticket, const bool state);

    ///< Номер квитируемой фразы СИ (Word)
    uint16_t getNumberTicketedSI() const;
    void setNumberTicketedSI(const uint16_t &value);

    ///< Идентификатор СИ (копируется из заголовка СИ)
    uint16_t getIdSI() const;
    void setIdSI(const uint16_t &value);

    ///< Режим ТЛМ (Word) , режим -1 в соответствующем разряде
    bool getModeTLM(const ModeTLM mode) const;
    uint16_t getModeTLM() const;
    void setModeTLM(const ModeTLM mode, const bool state);
    void resetModeTLM();
    void resetBandTLM();

    ///< Счетчик кадров ТЛМ (Word)
    uint16_t getCounterTLM() const;
    void setCounterTLM(const uint16_t &value);

    // Режим РКО (Word) , режим -1 в соответствующем разряде
    bool getModeORM(const uint8_t mode);
    void setModeORM(const uint8_t mode,const bool state);

    ///< Счетчик угловых измерений
    uint16_t getCounterAngle() const;
    void setCounterAngle(const uint16_t &value);

    ///< Счетчик измерений дальности
    uint16_t getCounterDistance() const;
    void setCounterDistance(const uint16_t &value);

    ///< Прогноз компенсации частоты доплера (Word), цена младшего разряда 10 Гц
    int16_t getDopplerFreqPrediction() const;
    void setDopplerFreqPrediction(const int16_t &value);

    ///< Отклонение частоты (Word), цена младшего разряда 10 Гц
    int16_t getFrequencyDeviation() const;
    void setFrequencyDeviation(const int16_t &value);

    ///< Авария устройства (Word) , авария - 1 в соответствующем разряде
    bool getAlarmDevice(const AlarmDevices device) const;
    uint16_t getAlarmDevice() const;
    void setAlarmDevices(const AlarmDevices device, const bool state);

    ///< Мощность передатчика (Word), в Ваттах
    uint16_t getPowerReceiver() const;
    void setPowerReceiver(const uint16_t &value);

    ///< Аттенюатор передатчика (Word), цена младшего разряда 0,1Дб
    uint8_t getAttenuator() const;
    void setAttenuator(const uint16_t &value);

    ///< Температура передатчика (Word), в гр. С
    int16_t getTempReceiver() const;
    void setTempReceiver(const int16_t &value);

    ///< Состояние системы (Word) , наличие режима -1 в соответствующем разряде
    bool getSystemState(const uint8_t index);
    void setSystemState(const uint8_t mode, const bool state);

    // Комплекты (Word) , 0 - 1-ый комплект, 1 - 2-ой комплект
    uint8_t getComplects(const uint8_t index);
    void setComplects(const uint8_t complect, const bool state);

    ///< Наличие обмена (Word) , обмен с устройством -1 в соответствующем разряде
    bool getSwap(const uint8_t index);
    void setSwap(const uint8_t numSwap, const bool state);

    ///< Режим АНТ (Word) , наличие режима -1 в соответствующем разряде, при программном или ручном режиме указывается наличие типа поправки
    bool getModeANT(const uint8_t mode);
    void setModeANT(const uint8_t mode, const bool state);

    uint16_t getValueSystemState() const;
    void setValueSystemState(const uint16_t state);

    uint16_t getValueComplects() const;
    void setValueComplects(const uint16_t state);

    uint16_t getValueSwap() const;

    int16_t getValueModeANT() const;
    void setValueModeANT(const int16_t mode);

    uint16_t getValueModeORM() const;
    void setValueModeORM(const uint16_t mode);

    void resetSwap();

    /*!
     * \brief Сбросить значения параметром ИФКТ
     */
    void resetInfoFunctionControl();

    /*!
     * @brief Шаблонная функция получения бита по индексу
     * @param value Переменная, из которой брать
     * @param index Индекс бита для установки
     * @return Флаг состояния
     */
    template<class T>
    bool getValueParamStation(const T& value, const uint8_t index) const
    {
        QMutexLocker lock(&_mutex);
        return (value >> (uint8_t)index) & 1u;
    }

private:
    void setDecoder(const uint16_t dec);
    void setTicketOTC(const uint16_t ticket);
    void setTicketSI(const uint16_t ticket);
    void setAlarmDevices(const uint16_t device);

    /*!
     * @brief Шаблонная функция записи бита по индексу
     * @param value Переменная, в которую необходимо записать
     * @param index Индекс бита для установки
     * @param state Состояние
     */
    template<class T>
    void setValueParamStation(T& value, const uint8_t index, const bool state)
    {
        QMutexLocker lock(&_mutex);
        if(state)
            value |= (1 << index);
        else
            value &= ~(1 << index);
    }
};

#endif // STRUCTFUNCTIONCONTROL_H
