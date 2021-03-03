#include "linkingFcc/infornation/SingleCommand/SingleCommand.h"

QString SingleCommand::getDateTime() const
{
    return dateTime;
}

void SingleCommand::setDateTime(const QString &value)
{
    dateTime = value;
}

uint8_t SingleCommand::typeTimeDelivery() const
{
    return _typeTimeDelivery;
}

void SingleCommand::setTypeTimeDelivery(uint8_t typeTimeDelivery)
{
    _typeTimeDelivery = typeTimeDelivery;
}

uint8_t SingleCommand::typeCommand() const
{
    return _typeCommand;
}

void SingleCommand::setTypeCommand(uint8_t typeCommand)
{
    _typeCommand = typeCommand;
}

uint16_t SingleCommand::numberCommand() const
{
    return _numberCommand;
}

void SingleCommand::setNumberCommand(const uint16_t &numberCommand)
{
    _numberCommand = numberCommand;
}

void SingleCommand::unserializeCommand(PD116OneTimeCommand otc)
{
    setTypeTimeDelivery(otc.typeTimeIssue);
    setTypeCommand(otc.typeCommand);
    setNumberCommand(createNumberCommand(otc));

    QDateTime dateTime = QDateTime::fromString("1900-01-01T00:00:00+03:00");

    dateTime = dateTime.addDays(otc.date);
    dateTime = dateTime.addSecs(otc.time);

    setDateTime(dateTime.toString("dd.MM.yyyy hh:mm:ss"));
}

void SingleCommand::unserializeCommand(const QJsonObject object)
{
    QJsonValue jv = object.value("cmd_num");
    if(!jv.isUndefined())
        setNumberCommand(jv.toInt());

    jv = object.value("cmd_type");
    if(!jv.isUndefined())
        setTypeCommand(jv.toInt());

    jv = object.value("cmd_type_delivery");
    if(!jv.isUndefined())
        setTypeTimeDelivery(jv.toInt());

    jv = object.value("cmd_dt");
    if(!jv.isUndefined())
        setDateTime(jv.toString());

}

uint16_t SingleCommand::createNumberCommand(PD116OneTimeCommand otc)
{
    return otc.onesNumCommand + otc.tensNumCommand * 10 + otc.hundredsNumCommand * 100 + otc.thousandsNumCommand * 1000;
}

void SingleCommand::resetSC()
{
    setTypeTimeDelivery(false);
    setTypeCommand(false);
    setNumberCommand(0);
    setDateTime("");
}
