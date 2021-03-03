#include "linkingFcc/infornation/SpecialCommandControl/SpecialCC.h"

QJsonObject SpecialCC::vectorData()
{
    QJsonObject data;

    data.insert("cmd_number", QJsonValue(static_cast<uint16_t>(_numCommand)));
    QJsonArray array;
    for(auto i = 0; i < params.size(); ++i)
        array.append(QJsonValue(params.at(i)));
    ///< если осутствуют параметры, не добавляем в json
    if(!array.isEmpty())
        data.insert("params", QJsonValue(array));
    return data;
}

QString SpecialCC::getParam(const Words word) const
{
    return params.at(static_cast<uint8_t>(word));
}

void SpecialCC::addParam(const QString& param)
{
    params.append(param);
}

void SpecialCC::clear()
{
    params.clear();
}

CommandsControl SpecialCC::numCommand() const
{
    return  _numCommand;
}

void SpecialCC::setNumCommand(const CommandsControl &numCommand)
{
    _numCommand = numCommand;
}

void SpecialCC::resetSpecialCC()
{
    setNumCommand(CommandsControl::IDLE);
    params.clear();

}
