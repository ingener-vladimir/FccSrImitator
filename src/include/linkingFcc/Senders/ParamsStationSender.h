#ifndef SENDERPARAMSSTATION_H
#define SENDERPARAMSSTATION_H

/*!
    \file
    \brief Класс отправки параметров станции в ЦУП
    \author Саньков Владимир
    \version 0.1
    \date декабрь 2019 г.
*/

#include <QByteArray>

#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/FactoryFormularFCC.h"
#include "linkingFcc/infornation/Params/ParamsCMS.h"
#include "TmiSender.h"
#include "TicketsSender.h"

class IJournal;

class SenderParamsStation
{
    QSharedPointer<IFactoryFormular> _factory{nullptr}; ///< Фабрика пакетов
    SenderTmi _senderTmi;                ///< Отправитель ТМИ
    int16_t _numberKA{0};

public:
    SenderParamsStation() {}
    /*!
     * \brief Установить фабрику пакетов
     * \param factory Фабрика
     */
    void setFactory(QSharedPointer<IFactoryFormular> factory);
    /*!
     * \brief Создать квитанцию для отправки в ЦУП
     */
    void createTicket(const int16_t ka);
    /*!
     * \brief Отправить ТМИ
     * \param object Данные ТМИ
     */
    void sendTMI(const QJsonObject &object, const int16_t ka, const int16_t seans, const int16_t vitok);
    /*!
     * \brief Остановить отправку ТМИ
     */
    void stopSendingTmi();
    /*!
     * \brief Тачать отправку ТМИ
     * \param format Формат ТМИ
     */
    void startSendingTmi(TmiFormat format);
    /*!
     * \brief Установить КА
     * \param lastKA КА
     */
    void setLastKA(const int16_t &lastKA);
    /*!
     * \brief Установить код заголовка
     * \param lastKA Код
     */
    void setCode(const CodeTicket code);
};

#endif // SENDERPARAMSSTATION_H
