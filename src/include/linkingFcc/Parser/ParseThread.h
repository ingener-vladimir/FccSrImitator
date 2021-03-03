#ifndef PARSETHREAD_H
#define PARSETHREAD_H

/*!
    \file
    \brief Класс для создания потока работы парсера
    \author Саньков Владимир
    \version 0.1
    \date декабрь 2019 г.
*/

#include <QThread>

#include "ParseWorker.h"

class ParseThread : public QObject
{
    Q_OBJECT

    QThread _thread;                ///< Поток
    QSharedPointer<ParseWorker> _worker{nullptr};
    QString _uuid{""};              ///< Уид устройства

public:
    ParseThread(TypeKit type,
                const QString& uuid,
                QSharedPointer<IJournal> journal,
                SenderParamsStation* sender);
    ~ParseThread();
    /*!
     * \brief Запуск потока
     * \param uuid Уид девайса
     * \param object Параметры
     */
    void run(const QString &uuid, const QJsonObject &object);
    /*!
     * \brief Установить уид девайса
     * \param uuid Уид
     */
    void setUuid(const QString &uuid);

signals:
    void finished();
};

#endif // PARSETHREAD_H
