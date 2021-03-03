#ifndef PACKAGEPROPAGATIONSIGNALDELAY_H
#define PACKAGEPROPAGATIONSIGNALDELAY_H

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/infornation/PropagationSignalDelay/PropagationSignalDelay.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"

class PackagePropagationSignalDelay : public BasePackage
{
    HeaderSr _header;
    QByteArray _array;

public:
    PackagePropagationSignalDelay(uint32_t msgNum,
                                  uint32_t prevMsgNum,
                                  QByteArray& array);
    PackagePropagationSignalDelay(QByteArray& array);
    ~PackagePropagationSignalDelay() {}
public:
    QByteArray serialize() override;
    void unserialize(QByteArray &) override {}
    void unserialize(PropagationSignalDelay& propagationSignalDelay);
};

#endif // PACKAGEPROPAGATIONSIGNALDELAY_H
