#ifndef STRUCTBANDTLM_H
#define STRUCTBANDTLM_H

#include <stdint.h>

/*!
 * @brief Время начала и время конца  запрашиваемой информации.
    Времена задаются в формате: дата - число дней, истекших с 1.1.1900  (WORD),
    время - число секунд, истекших с начала суток (DWORD)
*/

#pragma pack(push,1)
struct BandTLM
{
    uint16_t date{0};
    uint32_t time{0};
};
#pragma pack(pop)

#endif // STRUCTBANDTLM_H
