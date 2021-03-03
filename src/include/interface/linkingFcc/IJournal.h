#ifndef IJOURNAL_H
#define IJOURNAL_H

#include <QString>
#include <QJsonArray>
#include <QList>
#include <QMutexLocker>
#include <QDateTime>

class IJournal
{
public:
    virtual ~IJournal() = default;
    /*!
     * \brief Запись события в журнал
     * \param event Событие
     * \param time Время
     */
    virtual void writeEvent(const QString& event) = 0;
    /*!
     * \brief Получить список общих событий
     * \return Массив Json
     */
    virtual QJsonArray getLogs() = 0;
    /*!
     * \brief Проверить, пустой ли журнал
     * \return Результат проверки
     */
    virtual bool isEmpty() = 0;
    /*!
     * \brief Установить время записи
     * \param time Время
     */
    virtual void setTime(uint64_t time) = 0;
};

#endif // IJOURNAL_H
