#include "linkingFcc/Parser/ParserVirtual.h"

void ParserVirtual::parseParams(const QJsonObject &obj)
{
    // Литер несущей
    QJsonValue jv = obj.value("CarryingLitera");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setLiter(jv.toInt());

    // Ант/нагр
    jv = obj.value("StateAntennaResistor");
    if(!jv.isUndefined())
        params.getInfoFC()->setSystemState(SystemState::TRANSMITTER, jv.toInt() == 1);

    // Пол ПРМ.А Л\П
    jv = obj.value("PolarizationDiffChannel");
    if(!jv.isUndefined())
        params.getInfoFC()->setComplects(Complects::POLAR_RECEIVER, jv.toInt() == 1);

    // Пол вверх Л\П
    jv = obj.value("PolarizationOnTransmit");
    if(!jv.isUndefined())
        params.getInfoFC()->setComplects(Complects::POLAR_UP, jv.toInt() == 1);

    jv = obj.value("ComplectMSHU");
    if(!jv.isUndefined())
    {
        params.setMSHUComplect(jv.toInt());
        params.getInfoFC()->setComplects(Complects::MSHY, jv.toInt() == 1 ? 1 : 0);
        params.getInfoFC()->setComplects(Complects::MSHY2, jv.toInt() == 2 ? 1 : 0);
        params.getInfoFC()->setComplects(Complects::MSHY3, jv.toInt() == 3 ? 1 : 0);
    }
}
