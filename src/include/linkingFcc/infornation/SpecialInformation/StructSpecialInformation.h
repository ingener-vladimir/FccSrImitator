#ifndef STRUCTSPECIALINFORMATION_H
#define STRUCTSPECIALINFORMATION_H

#include <stdint.h>

/*! @brief Структура измерительной посылки скорости
    Длина информационной части массива СИ в 16р. словах (Word)
    Длина фразы = 32 (Word) (=2,4,32)
    Идентификатор СИ *
    Слова СИ (integer)
    Длина транзитной СИ не может превышать 64 Кбайта.
*/
#pragma pack(push,1)
struct StructSpecialInformation
{
    uint16_t length;        ///< Длина информационной части массива СИ в 16р. словах (Word)
    uint16_t phraseLength;  //</ Длина фразы = 32 (Word) (=2,4,32)
    uint16_t idSI;          ///< Идентификатор СИ *
    int32_t code[32765];    //</ Слова СИ
};
#pragma pack(pop)

#endif // STRUCTSPECIALINFORMATION_H
