#include "linkingFcc/Senders/ParamsStationSender.h"

void SenderParamsStation::createTicket(const int16_t ka)
{
    if(_factory)
    {
        FactoryFormularFCC* factory = dynamic_cast<FactoryFormularFCC*>(_factory.data());
        if(factory)
        {
            factory->setLastKA(ka);
            auto head = factory->getLastHeader();
            factory->addTicket(head);
        }
    }
}

void SenderParamsStation::sendTMI(const QJsonObject &object, const int16_t ka, const int16_t seans, const int16_t vitok)
{
    if(_factory)
    {
        QList<QByteArray> list = _senderTmi.createCurrentTmi(object, ka, seans, vitok);
        FactoryFormularFCC* factory = dynamic_cast<FactoryFormularFCC*>(_factory.data());
        if(factory)
        {
            for(auto& lt : list)
                factory->addPackageDirective152(_senderTmi.format(), lt);
        }
    }
}

void SenderParamsStation::stopSendingTmi()
{
    _senderTmi.stopSendingTmi();
}

void SenderParamsStation::startSendingTmi(TmiFormat format)
{
    _senderTmi.startSendingTmi(format);
}

void SenderParamsStation::setLastKA(const int16_t &lastKA)
{
    _numberKA = lastKA;
    if(_factory)
    {
        FactoryFormularFCC* factory = dynamic_cast<FactoryFormularFCC*>(_factory.data());
        if(factory)
            factory->setLastKA(lastKA);
    }
}

void SenderParamsStation::setCode(const CodeTicket code)
{
    if(_factory)
    {
        FactoryFormularFCC* factory = dynamic_cast<FactoryFormularFCC*>(_factory.data());
        if(factory)
            factory->setCode(code);
    }
}

void SenderParamsStation::setFactory(QSharedPointer<IFactoryFormular> factory)
{
    _factory = factory;
    setLastKA(_numberKA);
}
