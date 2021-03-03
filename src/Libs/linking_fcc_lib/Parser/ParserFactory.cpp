#include "linkingFcc/Parser/ParserFactory.h"

ParserFactory::ParserFactory(TypeKit type,
                             QSharedPointer<IJournal> journal,
                             SenderParamsStation *sender)
{
    switch(type)
    {
    case TypeKit::MODEM:
        _parser = QSharedPointer<ParserModem>(new ParserModem(journal, sender));
        break;

    case TypeKit::CONVERTER_UP:
        break;

    case TypeKit::AMPLIFIER:
        _parser = QSharedPointer<ParserAmplifier>(new ParserAmplifier());
        break;

    case TypeKit::MSHY:
        break;

    case TypeKit::ANTENNA:
        _parser = QSharedPointer<ParserAntenna>(new ParserAntenna(journal));
        break;

    case TypeKit::VIRTUAL:
        _parser = QSharedPointer<ParserVirtual>(new ParserVirtual());
        break;

    case TypeKit::METEOCOMPLEX:
        _parser = QSharedPointer<ParserMeteo>(new ParserMeteo());
        break;

    default:
        break;
    }
}

ParserFactory::~ParserFactory()
{
    _parser.reset();
    _parser = nullptr;
}

QSharedPointer<IParserParams> ParserFactory::getPtrParserParams()
{
    return _parser;
}
