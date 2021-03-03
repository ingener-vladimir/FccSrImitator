#ifndef SINGLECOMMAND_H
#define SINGLECOMMAND_H

/*!
    \file
    \brief Класс хранения разовой команды
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include <stdint.h>
#include <QString>
#include <QDateTime>
#include <QJsonObject>

#include "linkingFcc/infornation/SingleCommand/StructSingleCommand.h"

enum class SINGLE_COMMAND : uint16_t
{
    SINGLE_COMMAND_6001 = 6001,
    SINGLE_COMMAND_6002 = 6002,
    SINGLE_COMMAND_6003 = 6003,
    SINGLE_COMMAND_6004 = 6004,
    SINGLE_COMMAND_6005 = 6005,
    SINGLE_COMMAND_6006 = 6006
};

class SingleCommand
{
    uint8_t _typeTimeDelivery{false}; ///< 1 - относительное время выдачи, 0 - фиксированное время выдачи,
    uint8_t _typeCommand{false};      ///< 1 - одноразовая команда, 0 - циклическая команда,
    uint16_t _numberCommand{0};       ///< номер команды
    QString dateTime{""};             ///< Дата и время

public:
    SingleCommand() {}

    uint8_t typeTimeDelivery() const;
    void setTypeTimeDelivery(uint8_t typeTimeDelivery);

    uint8_t typeCommand() const;
    void setTypeCommand(uint8_t typeCommand);

    uint16_t numberCommand() const;
    void setNumberCommand(const uint16_t &numberCommand);

    QString getDateTime() const;
    void setDateTime(const QString &value);

    /*!
     * \brief Распаковать разовую команду
     * \param otc Данные разовой команды
     */
    void unserializeCommand(PD116OneTimeCommand otc);

    void resetSC();
    /*!
     * \brief Распаковать разовую команду
     * \param otc Данные разовой команды
     */
    void unserializeCommand(const QJsonObject object);

private:
    /*!
     * \brief Создание номера команды из единиц, десяток, сотен, тысяч
     * \param otc Структура
     * \return Номер команды
     */
    uint16_t createNumberCommand(PD116OneTimeCommand otc);
};

#endif // SINGLECOMMAND_H
