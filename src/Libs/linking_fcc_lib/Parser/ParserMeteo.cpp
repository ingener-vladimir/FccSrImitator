#include "linkingFcc/Parser/ParserMeteo.h"

void ParserMeteo::parseParams(const QJsonObject &obj)
{
    // wind direction
    QJsonValue jv = obj.value("windDirectionInstant");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setWindDirection(jv.toDouble());

    // wind speed
    jv = obj.value("faithSpeedInstant");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setWindSpeed(jv.toDouble());

    // humidity
    jv = obj.value("humidityInstant");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setHumidity(jv.toDouble());

    // temerature
    jv = obj.value("temperatureInstant");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setTemp((uint8_t)jv.toDouble());

    // preasure
    jv = obj.value("pressureInstant");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setWord33(jv.toDouble());
}
