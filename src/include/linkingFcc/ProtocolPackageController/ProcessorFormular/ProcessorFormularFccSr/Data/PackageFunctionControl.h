#ifndef PACKAGEFUNCTIONCONTROL_H
#define PACKAGEFUNCTIONCONTROL_H

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"
#include "linkingFcc/infornation/FunctionControl/fcc-sr/FunctionControlSr.h"

class PackageFunctionControl : public BasePackage
{
    HeaderSr _header;
    QByteArray _array;

    union
    {
        struct
        {
            sr::HeaderSr headerPkg;
            StructFunctionControlSr control;
        } _data_block;
        uint8_t _data[sizeof(sr::HeaderSr) + sizeof(StructFunctionControlSr)];
    };
public:
    PackageFunctionControl(uint32_t msgNum,
                           uint32_t prevMsgNum,
                           QByteArray array);
    PackageFunctionControl(QByteArray& array);
    ~PackageFunctionControl() {}

public:
    QByteArray serialize() override;
    void unserialize(QByteArray &) override {}
    void unserialize(FunctionControlSr &functionControlSr);
};

#endif // PACKAGEFUNCTIONCONTROL_H
