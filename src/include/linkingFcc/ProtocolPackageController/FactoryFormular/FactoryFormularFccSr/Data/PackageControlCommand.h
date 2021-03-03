#ifndef PACKAGECONTROLCOMMAND_H
#define PACKAGECONTROLCOMMAND_H

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"
#include "linkingFcc/infornation/CommandControl/fcc-sr/ControlCommandSr.h"

class PackageControlCommand : public BasePackage
{
    HeaderSr _header;
    QByteArray _array;

    union
    {
        struct
        {
            sr::HeaderSr headerPkg;
            StructControlCommand structControlCommand;
        } _data_block;
        uint8_t _data[sizeof(sr::HeaderSr) + sizeof(StructControlCommand)];
    };
public:
    PackageControlCommand(uint32_t msgNum,
                          uint32_t prevMsgNum,
                          QByteArray& array);
    PackageControlCommand(QByteArray &array);

    QByteArray serialize() override;
    void unserialize(QByteArray &) override {}
    void unserialize(ControlCommandSr &controlCommandSr);
};

#endif // PACKAGECONTROLCOMMAND_H
