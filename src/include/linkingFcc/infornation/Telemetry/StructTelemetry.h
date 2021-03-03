#ifndef STRUCTTELEMETRY_H
#define STRUCTTELEMETRY_H

#include <stdint.h>

#pragma pack(push,1)
struct HeaderTelemetry
{
    uint16_t word1;
    uint16_t word2;
    uint16_t word3;
    uint16_t word4;
    uint16_t word5;
    uint16_t word6;
    uint16_t word7;
};
#pragma pack(pop)

#pragma pack(push,1)
struct StructTelemetry
{
    HeaderTelemetry headerTelemetry;
    uint16_t information[512];
};
#pragma pack(pop)


#endif // STRUCTTELEMETRY_H
