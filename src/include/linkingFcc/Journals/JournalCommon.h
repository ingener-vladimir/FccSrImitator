#ifndef JOURNALCOMMON_H
#define JOURNALCOMMON_H

/*!
    \file
    \brief Класс-наследник работы с журналом регистрации событий
    \author Саньков Владимир
    \version 0.1
    \date декабрь 2019 г.
*/

#include "interface/linkingFcc/IJournal.h"

class JournalCommon : public IJournal
{
    QList<QString> _events; ///< Список общих событий
    QMutex _mutex;

    uint64_t _time{0};

public:
    JournalCommon() {}
    ~JournalCommon() {}
    /*!
     * \brief Получить список общих событий
     * \return Массив Json
     */
    QJsonArray getLogs() override;
    /*!
     * \brief Проверить, пустой ли журнал
     * \return Результат проверки
     */
    bool isEmpty() override;
    /*!
     * \brief Запись события в журнал
     * \param event Событие
     * \param time Время
     */
    void writeEvent(const QString& event) override;
    /*!
     * \brief Установить время записи
     * \param time Время
     */
    void setTime(uint64_t time) override;
};

#endif // JOURNALCOMMON_H

