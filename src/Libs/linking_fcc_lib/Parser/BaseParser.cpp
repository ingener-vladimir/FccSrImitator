#include "linkingFcc/Parser/BaseParser.h"

BaseParser::BaseParser(QSharedPointer<IJournal> journal, SenderParamsStation* sender)
    : _journal(journal), _sender(sender)
{
}

BaseParser::~BaseParser()
{

}


