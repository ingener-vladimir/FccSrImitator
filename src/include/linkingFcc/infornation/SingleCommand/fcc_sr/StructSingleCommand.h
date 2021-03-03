#ifndef STRUCTSINGLECOMMANDSR_H
#define STRUCTSINGLECOMMANDSR_H

#include <stdint.h>

#pragma pack(push,1)
struct StructSingleCommand
{
    uint8_t reserve1 : 1;
    uint8_t reserve2 : 1;
    uint8_t typeCommand : 1;         ///< 1 - одноразовая команда, 0 - циклическая команда
    uint8_t addition : 1;            ///< дополнение до четности
    uint16_t code: 11;               ///< код команды
    uint8_t reserve3 : 1;
    uint16_t word2;                  ///< always 0
};
#pragma pack(pop)

#endif // STRUCTSINGLECOMMANDSR_H
