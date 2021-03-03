#include "linkingFcc/Parser/ParseWorker.h"

ParseWorker::ParseWorker(TypeKit type,
                         QSharedPointer<IJournal> journal,
                         SenderParamsStation *sender)
    : _type(type), _journal(journal), _sender(sender)
{

}

ParseWorker::~ParseWorker()
{
    _factory.reset();
    _factory = nullptr;
}

void ParseWorker::initThread()
{
    if(!_factory)
        _factory = QSharedPointer<ParserFactory>(new ParserFactory(_type, _journal, _sender));

    auto parser = _factory->getPtrParserParams();
    if(parser)
        parser->parseParams(_object);

    emit finished();
}

void ParseWorker::setJsonObject(const QJsonObject &object)
{
    _object = object;
}
