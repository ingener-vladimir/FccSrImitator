#ifndef COMMANDCONTROL_H
#define COMMANDCONTROL_H

/*!
    \file
    \brief Класс команды управления
    \author Саньков Владимир
    \version 0.1
    \date октябрь 2019 г.
*/

#include "BaseCommandControl.h"

class CommandControl : public BaseCommandControl
{

public:
    CommandControl() {}
    ~CommandControl() {}

    /*!
     * \brief Парсинг команды, которая пришла из ЦУП
     * \param nKA Номер КА
     * \param header Заголовок
     */
    void unserializeCommand(uint16_t nKA, HeaderControlCommand& header) override;
};

#endif // COMMANDCONTROL_H
