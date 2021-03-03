#ifndef IFCSENDERFACTORY_H
#define IFCSENDERFACTORY_H

#include "interface/linkingFcc/IIfcSender.h"

class IPackageController;

class IfcSenderFactory
{
    IfcSenderFactory() {}
public:
    static QSharedPointer<IIfcSender> createIfcSender(QSharedPointer<IPackageController> packageController);
};

#endif // IFCSENDERFACTORY_H
