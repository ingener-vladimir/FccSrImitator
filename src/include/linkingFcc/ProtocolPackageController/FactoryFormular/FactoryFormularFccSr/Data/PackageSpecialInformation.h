#ifndef PACKAGESPECIALINFORMATION_H
#define PACKAGESPECIALINFORMATION_H

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/infornation/SpecialInformation/fcc-sr/SpecialInformationSr.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"

class PackageSpecialInformation : public BasePackage
{
    HeaderSr _header;
    QByteArray _array;

public:
    PackageSpecialInformation(uint32_t msgNum,
                              uint32_t prevMsgNum,
                              QByteArray& array);
    PackageSpecialInformation(QByteArray& array);
public:
    QByteArray serialize() override;
    void unserialize(QByteArray &) override {}
    void unserialize(SpecialInformationSr &specialInformationSr);
};

#endif // PACKAGESPECIALINFORMATION_H
