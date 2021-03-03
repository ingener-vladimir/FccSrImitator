#ifndef PARSEREVENTS_H
#define PARSEREVENTS_H

/*!
    \file
    \brief Класс для упраления работой парсингов событий
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include <QMap>
#include <QUuid>

#include "ParseThread.h"

/// Структура для хранения информации комплекта устройства
struct Kits
{
    TypeKit type{TypeKit::UNDEFINED};
    int8_t kit{0};

    Kits() {}
    Kits(const TypeKit _type, const int8_t _kit)
        : type(_type), kit(_kit) {}

    bool operator==(const Kits& kits) const
    {
        return (type == kits.type) && (kit == kits.kit);
    }
};

static QMap<Swap, QString> MAP_SWAP
{
    {Swap::MODEM_COMPLECT_1, ""},
    {Swap::MODEM_COMPLECT_2, ""},
    {Swap::LIU, ""},
    {Swap::CONVERTER_UP_COMPLECT_1, ""},
    {Swap::CONVERTER_UP_COMPLECT_2, ""},
    {Swap::CONVERTER_DOWN_COMPLECT_1, ""},
    {Swap::CONVERTER_DOWN_COMPLECT_2, ""},
    {Swap::NP_1, ""},
    {Swap::NP_2, ""},
    {Swap::AMPLIFIER1, ""},
    {Swap::AMPLIFIER2, ""},
    {Swap::AYY495_COMPLECT_1, ""},
    {Swap::AYY495_COMPLECT_2, ""},
    {Swap::YYP, ""},
    {Swap::METEOSTATION, ""},
    {Swap::SCU1, ""},
    {Swap::SCU2, ""},
    {Swap::TEST_TRANSLATION, ""},
    {Swap::ANT, ""},
    {Swap::CORTEX, ""}
};

class ParserEvents
{

    QMap<TypeKit, QSharedPointer<ParseThread>> _mapParser;
    QMap<Swap, Kits> _mapSwap;
    QSharedPointer<IJournal> _journal{nullptr};
    SenderParamsStation* _sender;
    /*!
     * \brief Добавить в мапу объект для проверки наличия обмена
     * \param type Тип устройства
     * \param uuid уид
     * \param kit Номер комплекта
     */
    void addSwap(TypeKit type, const QString &uuid, const int8_t kit);

public:
    ParserEvents(QSharedPointer<IJournal> _journal);
    ~ParserEvents();

    /*!
     * \brief Распарсить событие от устройства
     * \param uuid Уид девайса
     * \param event Данные
     */
    void parseEvents(const QString &uuid, const QJsonDocument &event);
    /*!
     * \brief Создать парсера устройства
     * \param type Тип девайса
     * \param uuid Уид
     * \param kit Номер комплекта
     */
    void createParser(TypeKit type, const QString& uuid, const int8_t kit);

    void setSender(SenderParamsStation *sender);
};

#endif // PARSEREVENTS_H
