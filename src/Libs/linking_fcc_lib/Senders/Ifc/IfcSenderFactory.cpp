#include "linkingFcc/Senders/Ifc/IfcSenderFactory.h"
#include "linkingFcc/Senders/Ifc/IfcSender.h"
#include "linkingFcc/Senders/Ifc/IfcSenderSr.h"

QSharedPointer<IIfcSender> IfcSenderFactory::createIfcSender(QSharedPointer<IPackageController> packageController)
{
    if(packageController->getFactory()->getTypeFactoryFormular() == TypeFactory::FCC)
        return QSharedPointer<IIfcSender>(new IfcSender(packageController));
    else if(packageController->getFactory()->getTypeFactoryFormular() == TypeFactory::FCC_SR)
        return QSharedPointer<IIfcSender>(new IfcSenderSr(packageController));

    return QSharedPointer<IIfcSender>();
}
