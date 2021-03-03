#ifndef PACKAGESINGLECOMMAND_H
#define PACKAGESINGLECOMMAND_H

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/infornation/SingleCommand/fcc_sr/SingleCommandSr.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"

class PackageSingleCommand : public BasePackage
{
    HeaderSr _header;
    QByteArray _array;

    union
    {
        struct
        {
            sr::HeaderSr headerPkg;
            StructSingleCommand structSingleCommand;
        } _data_block;
        uint8_t _data[sizeof(sr::HeaderSr) + sizeof(StructSingleCommand)];
    };
public:
    PackageSingleCommand(uint32_t msgNum,
                         uint32_t prevMsgNum,
                         QByteArray& array);
    PackageSingleCommand(QByteArray& array);

public:
    QByteArray serialize() override;
    void unserialize(QByteArray &) override {}
    void unserialize(SingleCommandSr &singleCommandSr);
};

#endif // PACKAGESINGLECOMMAND_H
