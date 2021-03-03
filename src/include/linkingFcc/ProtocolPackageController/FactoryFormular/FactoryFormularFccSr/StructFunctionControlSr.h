#ifndef STRUCTFUNCTIONCONTROLSR_H
#define STRUCTFUNCTIONCONTROLSR_H

#include <stdint.h>

#pragma pack(push,1)
struct StructFunctionControlSr
{
    uint64_t reserve1;
    uint64_t reserve2;
    int32_t offsetTime;              ///< Расхождение между секундными метками оцифровки времени НАП и текущего времени в микросекундах (LongInt), цена младшего разряда 1 мкс из модема
    uint16_t systemState;            ///< Состояние системы (Word) , наличие режима -1 в соответствующем разряде
    uint16_t liter;                  ///< Литер несущей (Word)
    uint16_t bandReceiver;           ///< Полоса приемника, Гц (Word)
    int16_t reserve3;
    int16_t doplerCorrection;        ///< Доплеровская поправка (Integer)
    uint16_t literPNS;               ///< Литер ПШС (Word)
    uint16_t literOTC;               ///< Литер РК (Word)
    uint16_t decoder;                ///< Выбор бортовых дешифраторов (Word) , выбор –1 в соответствующем разряде
    int16_t signalPower;             ///< Уровень сигнала на входе МШУ, пересчитанный со входа модема Т-Б, в ДбВт
    uint16_t reserve4;
    uint16_t readies;                ///< Готовность
    uint64_t reserve5;
    uint64_t reserve6;
    uint64_t reserve7;
    uint16_t reserve8;
    uint8_t reserve9;
    uint16_t ticketOTC;              ///< Квитанция РК (Word) , тип квитанции -1 в соответствующем разряде
    uint16_t numberTicketedOTC;      ///< Номер квитируемой РК(ОРК) (Word)
    uint16_t ticketSI;               ///< Квитанция СИ (Word) , тип квитанции и состояние -1 в соответствующем разряде
    uint16_t numberTicketedSI;       ///< Номер квитируемой фразы СИ (Word)
    uint16_t idSI;                   ///< Идентификатор СИ (копируется из заголовка СИ)
    uint16_t modeTLM;                ///< Режим ТЛМ (Word) , режим -1 в соответствующем разряде
    uint16_t counterTLM;             ///< Счетчик кадров ТЛМ (Word)
    uint16_t reserve10;
    uint16_t reserve11;
    uint16_t reserve12;
    uint16_t reserve13;
    uint16_t reserve14;
    uint16_t reserve15;
    uint16_t reserve16;

};
#pragma pack(pop)
#endif // STRUCTFUNCTIONCONTROLSR_H
