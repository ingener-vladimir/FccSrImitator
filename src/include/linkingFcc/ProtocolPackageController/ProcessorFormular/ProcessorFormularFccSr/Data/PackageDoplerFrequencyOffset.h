#ifndef PACKAGEDOPLERFREQUENCYOFFSET_H
#define PACKAGEDOPLERFREQUENCYOFFSET_H

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/infornation/DoplerFrequencyOffset/DoplerFrequencyOffset.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"

class PackageDoplerFrequencyOffset : public BasePackage
{
    HeaderSr _header;
    QByteArray _array;

public:
    PackageDoplerFrequencyOffset(uint32_t msgNum, uint32_t prevMsgNum, QByteArray& array);
    PackageDoplerFrequencyOffset(QByteArray &array);
    ~PackageDoplerFrequencyOffset() {}

    QByteArray serialize() override;
    void unserialize(QByteArray &) override {}
    void unserialize(DoplerFrequencyOffset& doplerFrequencyOffset);
};

#endif // PACKAGEDOPLERFREQUENCYOFFSET_H
