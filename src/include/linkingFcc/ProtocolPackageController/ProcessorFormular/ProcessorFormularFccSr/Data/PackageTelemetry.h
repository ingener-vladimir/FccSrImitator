#ifndef PACKAGETELEMETRY_H
#define PACKAGETELEMETRY_H

#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"
#include "linkingFcc/infornation/Telemetry/Telemetry.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"
#include "linkingFcc/infornation/Telemetry/StructTelemetry.h"

class PackageTelemetry : public BasePackage
{
    HeaderSr _header;
    QByteArray _array;

    union
    {
        struct
        {
            sr::HeaderSr headerPkg;
            StructTelemetry telemetry;
        } _data_block;
        uint8_t _data[sizeof(sr::HeaderSr) + sizeof(StructTelemetry)];
    };

public:
    PackageTelemetry(uint32_t msgNum,
                     uint32_t prevMsgNum,
                     QByteArray& array);
    PackageTelemetry(QByteArray& array);
    ~PackageTelemetry() {}

public:
    QByteArray serialize() override;
    void unserialize(QByteArray &) override {}
    void unserialize(Telemetry& telemetry);
};

#endif // PACKAGETELEMETRY_H
