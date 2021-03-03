#include "linkingFcc/Senders/Ifc/IfcSender.h"
#include "utils/ValueToByteArray.h"

IfcSender::IfcSender(QSharedPointer<IPackageController> protocolPackageController)
    : BaseIfcSender(protocolPackageController)
{
}

void IfcSender::process()
{
    ParamsCMS& params = ParamsSingleton::getInstance();

    QByteArray array;
    params.createByteArrayForSendIFCT(array);
    if(_protocolPackageController)
    {
        FactoryFormularFCC* factory =  dynamic_cast<FactoryFormularFCC*>(_protocolPackageController->getFactory().data());
        if(!isActive && params.getInfoFC()->getSystemState(SystemState::READY_ES))
        {
            uint16_t state = params.getInfoFC()->getRefInfoControl()->getValueSystemState();
            state &= ~(1 << 14);
            QByteArray ar;
            ar.append(functions::toByteArrayLE<uint16_t>(state));
            array.replace(20, 2, ar);
        }
        factory->setSeansPrm(params.getNumberSeans(), params.getNumberVitok());
        factory->setNipNumber(params.getNumberNIP());
        factory->setLastKA(params.getNumberKA());
        factory->addPackageDirective155(array);
    }
}

