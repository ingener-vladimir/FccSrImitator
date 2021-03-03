#ifndef STRUCTHEADER_H
#define STRUCTHEADER_H

/*!
    \file
    \brief Структура унифицированного заголовка
    \author Саньков Владимир
    \version 0.1
    \date октябрь 2019 г.
    Заголовок является универсальным и используется со всеми типами ИП.
*/

#include <stdint.h>
#include "linkingFcc/Structs/Directive.h"
#include "linkingFcc/Structs/TypeInformation.h"
#include "linkingFcc/Structs/CodeTicket.h"

namespace daq
{

#pragma pack(push,1)
struct Header
{
    uint8_t RAZD;                           ///< Резерв (константа)
    Directive NDIR;                         ///< № Директивы
    uint32_t NPrd;                          ///< Номер передаваемого пакета
    uint32_t NPrm;                          ///< Номер последнего принятого пакета
    TypeInfo NFORM;                         ///< Вид информации (ВИ)
    int16_t NKA{0};                         ///< № КА
    int16_t NNIP_KTC;                       ///< № Станции*100+№Ствола
    uint8_t NSEANS{0};                      ///< № Сеанса на витке
    int16_t NVITKA{0};                      ///< № Витка
    int16_t LenInfo{0};                     ///< Длина информации прямого/обратного канала
    CodeTicket Code{CodeTicket::TICKET_00}; ///< Код квитанции на директиву или циклический номер инициативного сообщения ЦУП
};
#pragma pack(pop)

}

#endif // STRUCTHEADER_H
