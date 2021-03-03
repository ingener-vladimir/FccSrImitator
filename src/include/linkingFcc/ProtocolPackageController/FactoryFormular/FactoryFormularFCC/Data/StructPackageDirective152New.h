#ifndef STRUCTPACKAGEDIRECTIVE152NEW_H
#define STRUCTPACKAGEDIRECTIVE152NEW_H

#include <stdint.h>
/** @brief Структура служебной части ПСК ТМИ (новый формат)
    1-й байт - 8-разрядное команднослужебное слово КСС - тип ПСК ТМИ 7, 6 и 5 разряды:
        000 - режим НП;
        101 - ВОСПР 1-й половины ОЗУ ТЛГ;
        111 - ВОСПР 2-й половины ОЗУ ТЛГ,
        0 разряд выставлен, остальные сняты;
    2-3 байты - Дата приема кадра ТМИ – число дней, истекших с 1.1.1900г. (дв. Код)
    4-7 байты - Время приема кадра ТМИ - число секунд, истекших с начала суток (дв. код)
    8 байт - Номер телеметрируемого КА
 */

#pragma pack(push,1)
struct TmiServicePartNew {
    uint8_t kss; // Принятого перевода термина "команднослужебное слово" не нашлось
    uint16_t date;
    uint32_t time;
    uint8_t kaNumber;
};

/** @brief Новый формат ТМИ кадра
    1-8 байты - Служебная часть ПСК ТМИ
    9-520 байты - Каналы псевдокадра ТМИ, они же "тело кадра ТМИ" в других протоколах
 */

struct PD152New
{
    TmiServicePartNew servicePart;
    uint8_t pseudoframeChannels[512];
};
#pragma pack(pop)

#endif // STRUCTPACKAGEDIRECTIVE152NEW_H
