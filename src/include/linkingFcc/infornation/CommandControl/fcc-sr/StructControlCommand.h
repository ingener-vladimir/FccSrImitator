#ifndef STRUCTCONTROLCOMMAND_H
#define STRUCTCONTROLCOMMAND_H

#include <stdint.h>

#include "ListControlCommand.h"

/*! @brief Структура команды управления
    1 слово - Номер КУ (Word)
    2 слово, 3 слово, 4 слово, 5 слово, 6 слово - Поле параметра
    (переменная структура, отсутствует, если параметра нет,
    от 1-го до 5- слов при наличии параметра )
*/

#pragma pack(push,1)
struct StructControlCommand
{
    ControlCommands numberCC; ///< Номер КУ
    int16_t words[5];
};
#pragma pack(pop)

#endif // STRUCTCONTROLCOMMAND_H
