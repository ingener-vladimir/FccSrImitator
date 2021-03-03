#include "linkingFcc/Parser/ParserEvents.h"

ParserEvents::ParserEvents(QSharedPointer<IJournal> journal)
    : _journal(journal)
{
    _mapSwap[Swap::MODEM_COMPLECT_1] = Kits(TypeKit::MODEM, 1);
    _mapSwap[Swap::MODEM_COMPLECT_2] = Kits(TypeKit::MODEM, 2);
    _mapSwap[Swap::CONVERTER_UP_COMPLECT_1] = Kits(TypeKit::CONVERTER_UP, 1);
    _mapSwap[Swap::CONVERTER_UP_COMPLECT_2] = Kits(TypeKit::CONVERTER_UP, 2);
    _mapSwap[Swap::CONVERTER_DOWN_COMPLECT_1] = Kits(TypeKit::CONVERTER_DOWN, 1);
    _mapSwap[Swap::CONVERTER_DOWN_COMPLECT_2] = Kits(TypeKit::CONVERTER_DOWN, 2);
    _mapSwap[Swap::NP_1] = Kits(TypeKit::NP, 1);
    _mapSwap[Swap::NP_2] = Kits(TypeKit::NP, 2);
    _mapSwap[Swap::AMPLIFIER1] = Kits(TypeKit::AMPLIFIER, 1);
    _mapSwap[Swap::AMPLIFIER2] = Kits(TypeKit::AMPLIFIER, 2);
    _mapSwap[Swap::AYY495_COMPLECT_1] = Kits(TypeKit::YAY495, 1);
    _mapSwap[Swap::AYY495_COMPLECT_2] = Kits(TypeKit::YAY495, 2);
    _mapSwap[Swap::YYP] = Kits(TypeKit::UNDEFINED, 1);
    _mapSwap[Swap::METEOSTATION] = Kits(TypeKit::METEOCOMPLEX, 1);
    _mapSwap[Swap::SCU1] = Kits(TypeKit::SCU, 1);
    _mapSwap[Swap::SCU2] = Kits(TypeKit::SCU, 2);
    _mapSwap[Swap::TEST_TRANSLATION] = Kits(TypeKit::TEST_TRANSLATION, 1);
    _mapSwap[Swap::ANT] = Kits(TypeKit::ANTENNA, 1);
}

ParserEvents::~ParserEvents()
{
    foreach(auto it, _mapParser)
    {
        it.reset();
        it = nullptr;
    }
}

void ParserEvents::parseEvents(const QString &uuid, const QJsonDocument &event)
{
    QJsonObject root = event.object();

    auto obj = root.value("dev_param").toObject();
    if(!obj.isEmpty())
    {
        foreach(auto it, _mapParser.values())
            it->run(uuid, obj);
    }

    ParamsCMS& params = ParamsSingleton::getInstance();
    if(MAP_SWAP.values().contains(uuid))
    {
        auto connection = root.value("dev_condition");
        if(!connection.isUndefined())
        {
            bool connect{false};
            if(connection.toInt() == 1 || connection.toInt() == 2)
                connect = true;
            params.getInfoFC()->setSwap(MAP_SWAP.key(uuid), connect);
        }
    }
}

void ParserEvents::addSwap(TypeKit type, const QString& uuid, const int8_t kit)
{
    if(type != TypeKit::UNDEFINED && kit > 0)
    {
        if(MAP_SWAP.values().contains(uuid))
        {
            if(_mapSwap[MAP_SWAP.key(uuid)].type == type
                    && _mapSwap[MAP_SWAP.key(uuid)].kit != kit)
                _mapSwap[MAP_SWAP.key(uuid)].kit = kit;
        }
        else
        {
            Kits kits(type, kit);
            MAP_SWAP[_mapSwap.key(kits)] = uuid;
        }
    }
}

void ParserEvents::createParser(TypeKit type, const QString& uuid, const int8_t kit)
{
    addSwap(type, uuid, kit);

    if(_mapParser.contains(type))
    {
        _mapParser.value(type)->setUuid(uuid);
        return;
    }

    QSharedPointer<ParseThread> parseFactory = QSharedPointer<ParseThread>(new ParseThread(type, uuid, _journal, _sender));
    _mapParser[type] = parseFactory;
}

void ParserEvents::setSender(SenderParamsStation* sender)
{
    _sender = sender;
}

