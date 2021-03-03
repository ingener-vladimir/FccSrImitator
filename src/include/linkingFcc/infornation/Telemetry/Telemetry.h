#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QDataStream>

#include "StructTelemetry.h"

class Telemetry
{
    uint16_t _date{0};
    QByteArray _information{"1"};

    static const uint16_t FRAME_TMI_LENGTH = 512;
public:
    Telemetry() {}

    QByteArray serialize();
    void unserialize(StructTelemetry& structTelemetry);

    QByteArray information() const;
    void setInformation(const QByteArray &information);
};

#endif // TELEMETRY_H
