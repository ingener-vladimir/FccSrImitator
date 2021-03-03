#ifndef SPECIALCC_H
#define SPECIALCC_H

/*!
    \file
    \brief Класс пользовательской команды управления
    \author Саньков Владимир
    \version 0.1
    \date декабрь 2019 г.
*/

#include <stdint.h>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

#include "linkingFcc/infornation/CommandControl/StructControlCommand.h"
#include "linkingFcc/Structs/Words.h"

class SpecialCC
{
    CommandsControl _numCommand{CommandsControl::IDLE}; ///< номер команды
    QVector<QString> params;                          ///< список параметров

public:
    SpecialCC() {}
    /*!
     * \brief Сформировать json для отправки в блокер
     * \return Объект json
     */
    QJsonObject vectorData();
    /*!
     * \brief Получить значение параметра из списка
     * \return Параметр
     */
    QString getParam(const Words word) const;
    /*!
     * \brief Добавить параметр в список параметров команды управления
     * \param param Параметр
     */
    void addParam(const QString &param);
    /*!
     * \brief Очистить список параметров
     */
    void clear();

    CommandsControl numCommand() const;
    void setNumCommand(const CommandsControl &numCommand);

    void resetSpecialCC();
};

#endif // SPECIALCC_H
