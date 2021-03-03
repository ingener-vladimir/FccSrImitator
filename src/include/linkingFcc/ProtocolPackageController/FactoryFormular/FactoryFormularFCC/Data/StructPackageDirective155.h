#ifndef STRUCTPACKAGEDIRECTIVE155_H
#define STRUCTPACKAGEDIRECTIVE155_H

/*!
  @brief Структура информации функционального контроля ИФКТ
*/

#include <stdint.h>

#pragma pack(push,1)
struct FunctionControl
{
   uint64_t currentTime;            ///< Текущее время ЗС(Posix)из модема
   uint64_t digitizationTime;       ///< Оцифровка времени НАП (Posix) с НП1
   int32_t offsetTime;              ///< Расхождение между секундными метками оцифровки времени НАП и текущего времени в микросекундах (LongInt), цена младшего разряда 1 мкс из модема
   uint16_t systemState;            ///< Состояние системы (Word) , наличие режима -1 в соответствующем разряде
   uint16_t liter;                  ///< Литер несущей (Word)
   uint16_t bandReceiver;           ///< Полоса приемника, Гц (Word)
   int16_t searchCorrection;        ///< Поисковая поправка (Integer)
   int16_t doplerCorrection;        ///< Доплеровская поправка (Integer)
   uint16_t literPNS;               ///< Литер ПШС (Word)
   uint16_t literOTC;               ///< Литер РК (Word)
   uint16_t decoder;                ///< Выбор бортовых дешифраторов (Word) , выбор –1 в соответствующем разряде
   uint16_t signalPower;            ///< Уровень сигнала на входе МШУ, пересчитанный со входа модема Т-Б, в ДбВт
   uint16_t complects;              ///< Комплекты (Word) , 0 - 1-ый комплект, 1 - 2-ой комплект
   uint16_t swap;                   ///< Наличие обмена (Word) , обмен с устройством -1 в соответствующем разряде
   uint16_t modeANT;                ///< Режим АНТ (Word) , наличие режима -1 в соответствующем разряде, при программном или ручном режиме указывается наличие типа поправки
   int32_t azimuthFBS;              ///< ДОС азимут (Integer), цена младшего разряда 10”U+0020
   uint16_t elevationFBS;           ///< ДОС угол места (Word), цена младшего разряда 10”
   int16_t correctionAzimuth;       ///< Поправка по азимуту (Smallint), цена младшего разряда 10”
   int16_t correctionElevation;     ///< Поправка по углу места (Smallint), цена младшего разряда 10”
   int32_t pointAzimuth;            ///< Точка азимута к которой движется антенна (Integer), цена младшего разряда 10”
   int16_t pointElevation;          ///< Точка угла места к которой движется антенна (Integer), цена младшего разряда 10”
   uint16_t keySCPI;                ///< Ключ СКЗИ
   uint16_t keyOSK;                 ///< Ключ БСК (бортовой сеансный ключ)
   uint16_t reserve_1;              ///< резерв
   uint16_t reserve_2;              ///< резерв
   uint16_t reserve_3;              ///< резерв
   uint16_t ticketOTC;              ///< Квитанция РК (Word) , тип квитанции -1 в соответствующем разряде
   uint16_t numberTicketedOTC;      ///< Номер квитируемой РК(ОРК) (Word)
   uint16_t ticketSI;               ///< Квитанция СИ (Word) , тип квитанции и состояние -1 в соответствующем разряде
   uint16_t numberTicketedSI;       ///< Номер квитируемой фразы СИ (Word)
   uint16_t idSI;                   ///< Идентификатор СИ (копируется из заголовка СИ)
   uint16_t modeTLM;                ///< Режим ТЛМ (Word) , режим -1 в соответствующем разряде
   uint16_t counterTLM;             ///< Счетчик кадров ТЛМ (Word)
   uint16_t modeORM;                ///< Режим РКО (Word) , режим -1 в соответствующем разряде
   uint8_t counterAngle;            ///< Счетчик угловых измерений
   uint8_t counterDistance;         ///< Счетчик измерений дальности
   uint16_t dopplerFreqPrediction;  ///< Прогноз компенсации частоты доплера (Word), цена младшего разряда 10 Гц
   uint16_t frequencyDeviation;     ///< Отклонение частоты (Word), цена младшего разряда 10 Гц
   uint16_t alarmDevice;            ///< Авария устройства (Word) , авария - 1 в соответствующем разряде
   uint16_t powerReceiver;          ///< Мощность передатчика (Word), в Ваттах
   uint8_t attenuator;              ///< Аттенюатор передатчика (Word), цена младшего разряда 0,1Дб
   uint8_t tempReceiver;            ///< Температура передатчика (Word), в гр. С
};
#pragma pack(pop)

#endif // STRUCTPACKAGEDIRECTIVE155_H
