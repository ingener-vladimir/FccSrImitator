#include "linkingFcc/infornation/CommandControl/BaseCommandControl.h"

uint16_t BaseCommandControl::numKA() const
{
    return _numKA;
}

void BaseCommandControl::setNumKA(const uint16_t &numKA)
{
    _numKA = numKA;
}

CommandsControl BaseCommandControl::numCommand() const
{
    return _numCommand;
}

void BaseCommandControl::setNumCommand(const CommandsControl &numCommand)
{
    _numCommand = numCommand;
}

uint16_t BaseCommandControl::getParam(const Words word) const
{
    return params.at((uint8_t)word);
}

void BaseCommandControl::setParams(const QVector<int16_t> &value)
{
    params = value;
}

uint16_t BaseCommandControl::getCurrentMode() const
{
    return _currentMode;
}

void BaseCommandControl::setCurrentMode(const uint16_t &currentMode)
{
    _currentMode = currentMode;
}

TypeSender BaseCommandControl::getCurrentType() const
{
    return _currentType;
}

void BaseCommandControl::setCurrentType(const TypeSender &currentType)
{
    _currentType = currentType;
}

void BaseCommandControl::addParam(const uint16_t param)
{
    params.append(param);
}

void BaseCommandControl::clear()
{
    params.clear();
}

void BaseCommandControl::setParamsSession(const int16_t session, const int16_t vitok)
{
    paramsSession.numberSeans = session;
    paramsSession.numberVitok = vitok;
}

ParamsSession BaseCommandControl::getParamsSession() const
{
    return paramsSession;
}

QJsonObject BaseCommandControl::vectorData()
{
    QJsonObject data;

    data.insert("KA", QJsonValue(_numKA));
    data.insert("mode", QJsonValue(_currentMode));
    data.insert("cmd_number", QJsonValue((uint16_t)_numCommand));
    data.insert("typeSender", QJsonValue((uint8_t)_currentType));
    QJsonArray array;
    for(auto i = 0; i < params.size(); ++i)
        array.append(QJsonValue(params.at(i)));
    ///< если осутствуют параметры, не добавляем в json
    if(!array.isEmpty())
        data.insert("params", QJsonValue(array));
    return data;
}


void BaseCommandControl::resetCommandControl()
{
    setNumCommand(CommandsControl::COMMAND_4000);
    setCurrentMode(4000);
    setCurrentType(TypeSender::FCC);
    params.clear();
}
