#include "linkingFcc/infornation/Telemetry/Telemetry.h"

QByteArray Telemetry::information() const
{
    return _information;
}

void Telemetry::setInformation(const QByteArray &information)
{
    _information = information;
}

QByteArray Telemetry::serialize()
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);

    uint16_t value{0};
    out << value;
    out << _date;
    out << value;
    out << value;
    out << value;
    out << value;
    out << value;
    array.append(_information);

    return array;
}

void Telemetry::unserialize(StructTelemetry& structTelemetry)
{
    _date = structTelemetry.headerTelemetry.word2;
    memcpy(_information.data(), structTelemetry.information, FRAME_TMI_LENGTH);
}
