#ifndef STRUCTPACKAGEDIRECTIVE112DISTANCE_H
#define STRUCTPACKAGEDIRECTIVE112DISTANCE_H

/*!
 * @brief Структура измерительной посылки дальности
    1-е, 2-е слова и 3-е (15-12рр) слово - 36-ти разрядный двоичный код времени
    с ценой младшего разряда, равной 1/217 c;
    3-е слово(11-0рр),
    4-е слово и 5-е слово(15-8рр) - 36-ти разрядный двоичный код дальности
    c ценой младшего разряда, равной 0,01 м;
    Код признака ИП "Д" - 5-е слово (7-4рр):="0010".
*/

#include <stdint.h>

#pragma pack(push,1)
struct PD112Distance
{
    uint64_t timeCode  :36;
    uint64_t distanceCode : 36;
    uint8_t reserve : 4;
    uint8_t code : 4;
};
#pragma pack(pop)

#endif // STRUCTPACKAGEDIRECTIVE112DISTANCE_H
