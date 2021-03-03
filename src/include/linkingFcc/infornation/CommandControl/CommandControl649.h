#ifndef COMMANDCONTROL649_H
#define COMMANDCONTROL649_H

#include "BaseCommandControl.h"

class CommandControl649 : public BaseCommandControl
{
public:
    CommandControl649() {}
    ~CommandControl649();
    /*!
     * \brief Парсинг команды, которая пришла из ЦУП
     * \param nKA Номер КА
     * \param header Заголовок
     */
    void unserializeCommand(uint16_t nKA, HeaderControlCommand& header) override;
};

#endif // COMMANDCONTROL649_H
