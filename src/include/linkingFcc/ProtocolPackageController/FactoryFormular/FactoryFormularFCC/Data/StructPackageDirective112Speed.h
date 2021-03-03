#ifndef STRUCTPACKAGEDIRECTIVE112SPEED_H
#define STRUCTPACKAGEDIRECTIVE112SPEED_H

/*!
 * @brief Структура измерительной посылки скорости
    1-е, 2-е слова и 3-е (15-12рр) слово - 36-ти разрядный двоичный код времени
    с ценой младшего разряда, равной 1/217 c;
    3-е слово(11-0рр),
    4-е слово и 5-е слово(15-12рр) - 32-х разрядный двоичный код скорости
    c ценой младшего разряда, равной 0,01 мм;
    Код признака ИП "С" - 5-е слово (7-4рр):="0011".
*/

#include <stdint.h>

#pragma pack(push,1)
struct PD112Speed
{
    uint64_t timeCode  :36;
    uint32_t speed_code;
    uint8_t reserve_1 : 4;
    uint8_t code : 4;
    uint8_t reserve_2 : 4;

};
#pragma pack(pop)

#endif // STRUCTPACKAGEDIRECTIVE112SPEED_H
