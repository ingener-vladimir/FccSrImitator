#include "linkingFcc/Senders/Ifc/IfcSenderSr.h"
#include "linkingFcc/infornation/Params/fcc-sr/ParamsSr.h"

IfcSenderSr::IfcSenderSr(QSharedPointer<IPackageController> protocolPackageController)
    : BaseIfcSender (protocolPackageController)
{
}

void IfcSenderSr::process()
{
    ParamsSr& paramsSr = ParamsSrSingleton::getInstance();
    if(_protocolPackageController)
    {
        FactoryFormularFccSr* fac = dynamic_cast<FactoryFormularFccSr*>(_protocolPackageController->getFactory().data());
        fac->addPackageFunctionControl(paramsSr.getFunctionControlSr().serialize());
    }
}
