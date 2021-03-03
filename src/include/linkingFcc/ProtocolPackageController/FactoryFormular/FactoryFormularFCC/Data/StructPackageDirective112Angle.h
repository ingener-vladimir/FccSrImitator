#ifndef STRUCTPACKAGEDIRECTIVE112ANGLE_H
#define STRUCTPACKAGEDIRECTIVE112ANGLE_H

/*!
 *  @brief Структура выходной информации угловых измерений.
  1-е и 2-е слова - 32 - х разрядный двоичный код времени
  с ценой младшего разряда 1/210 секунды,
  3-е и 4-е слова - 32-х разрядный двоичный код азимута или угла места
  с ценой младшего разряда 1 угловая секунда,
  Код признака ИП "азимута" - 5-е слово (7-4рр):= "0110".
  Код признака ИП "угла места" - 5-е слово (7-4рр):= "0111".
*/
#include <stdint.h>

#pragma pack(push,1)
struct PD112Angle
{
    uint32_t timeCode;
    uint32_t angleCode;
    uint8_t reserve_1;
    uint8_t code : 4;
    uint8_t reserve_2 : 4;
};
#pragma pack(pop)

#endif // STRUCTPACKAGEDIRECTIVE112ANGLE_H
