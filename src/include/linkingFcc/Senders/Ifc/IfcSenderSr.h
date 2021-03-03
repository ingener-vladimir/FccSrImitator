#ifndef IFCSENDERSR_H
#define IFCSENDERSR_H

#include "BaseIfcSender.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/FactoryFormularFccSr.h"

class IfcSenderSr : public BaseIfcSender
{
public:
    IfcSenderSr(QSharedPointer<IPackageController> protocolPackageController);
    ~IfcSenderSr() {}

public:
    void process() override;
};

#endif // IFCSENDERSR_H
