#ifndef SENDERTMI_H
#define SENDERTMI_H

/*!
    \file
    \brief Класс отправки ТМИ в ЦУП
    \author Фуфаев Никита
    \version 0.1
    \date ноябрь 2019 г.
*/

#include <QObject>
#include <QDataStream>
#include <QDateTime>

#include "linkingFcc/Structs/TmiFormat.h"
#include "linkingFcc//FileWorker/FileWorkerTmi.h"

class SenderTmi : public QObject
{
    Q_OBJECT

    bool _isSendingTmi{false}; ///< Флаг состояния отправки ТМИ в ЦУП
    TmiFormat _format{TmiFormat::NEW_TMI_FORMAT}; ///< Формат пакетов ТМИ, отправляемых в ЦУП
    int16_t _numberKA{-1};
    int16_t _numberSeans{-1};
    int16_t _numberVitok{-1};
    QDateTime _receptionTime;
    /*!
     * \brief Сформировать пакет ТМИ для отправки в ЦУП
     */
    QByteArray createTmiPackage(const QJsonObject &messageObject);

public:
    /*!
     * \brief Отправлять текущую ТМИ в ЦУП
     * \param format Формат пакетов ТМИ
     */
    void startSendingTmi(TmiFormat format);

    /*!
     * \brief Перестать отправлять текущую ТМИ в ЦУП
     */
    void stopSendingTmi();

    /*!
     * \brief Отправить текущий кадр ТМИ
     */
    QList<QByteArray> createCurrentTmi(const QJsonObject& object,
                                       const int16_t ka,
                                       const int16_t seans,
                                       const int16_t vitok);
    /*!
     * \brief Получить формат ТЛМ
     * \return Формат
     */
    TmiFormat format() const;
};

#endif // SENDERTMI_H
