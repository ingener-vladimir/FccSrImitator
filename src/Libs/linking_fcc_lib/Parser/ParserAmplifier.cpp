#include "linkingFcc/Parser/ParserAmplifier.h"

void ParserAmplifier::parseParams(const QJsonObject &obj)
{
    params.getInfoFC()->getRefInfoControl()->setPowerReceiver(0);
    params.getInfoFC()->getRefInfoControl()->setAttenuator(0);
    params.getInfoFC()->setSystemState(SystemState::RADIATION_AMPLIFIER_1, false);
    params.getInfoFC()->setSystemState(SystemState::RADIATION_AMPLIFIER_2, false);
    params.getInfoFC()->getRefInfoControl()->setTempReceiver(0);

    /// мощность
    QJsonValue jv = obj.value("power");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setPowerReceiver(jv.toInt());

    /// аттенюатор
    jv = obj.value("att");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setAttenuator(jv.toInt());

    /// температура
    jv = obj.value("outletTemp");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setTempReceiver(jv.toInt());

    // Изл. УМ1
    jv = obj.value("emission");
    if(!jv.isUndefined()) {
        int complect = params.getInfoFC()->getComplects(Complects::AMPLIFIER);
        if(complect > 0)
            params.getInfoFC()->setSystemState(complect == 1 ? SystemState::RADIATION_AMPLIFIER_1 : SystemState::RADIATION_AMPLIFIER_2, jv.toBool());
    }
}
