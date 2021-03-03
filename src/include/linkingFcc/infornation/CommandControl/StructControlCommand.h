#ifndef STRUCTCONTROLCOMMANDAND_H
#define STRUCTCONTROLCOMMANDAND_H

#include "linkingFcc/infornation/CommandControl/CommandControlEnum.h"
/*! @brief Структура транцитной команды управления
    1 слово - Номер КУ (Word)
    2 слово, 3 слово, 4 слово, 5 слово, 6 слово - Поле параметра
    (переменная структура, отсутствует, если параметра нет,
    от 1-го до 5- слов при наличии параметра )
*/

#pragma pack(push,1)
struct HeaderControlCommand
{
    CommandsControl numberCC; ///< Номер КУ
    int16_t words[5];
};
#pragma pack(pop)

#endif // STRUCTCONTROLCOMMANDAND_H
