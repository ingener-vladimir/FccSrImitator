#ifndef PARSEWORKER_H
#define PARSEWORKER_H

/*!
    \file
    \brief Класс для работы для создания и работы парсеров
    \author Саньков Владимир
    \version 0.1
    \date декабрь 2019 г.
*/

#include <QObject>

#include "ParserFactory.h"

class ParseWorker : public QObject
{
    Q_OBJECT

    QSharedPointer<ParserFactory> _factory{nullptr};
    TypeKit _type{TypeKit::UNDEFINED};
    QJsonObject _object;
    QSharedPointer<IJournal> _journal{nullptr};
    SenderParamsStation* _sender{nullptr};

public:
    ParseWorker(TypeKit type,
                QSharedPointer<IJournal> journal,
                SenderParamsStation* sender);
    ~ParseWorker();
    /*!
     * \brief Функция для инициализации праметров работы потокаы
     */
    void initThread();
    /*!
     * \brief Установить QJsonObject с полученными данными
     * \param object
     */
    void setJsonObject(const QJsonObject& object);

signals:
    /*!
     * \brief Сигнал, отправляемый по завершению потока
     */
    void finished();
};

#endif // PARSEWORKER_H
