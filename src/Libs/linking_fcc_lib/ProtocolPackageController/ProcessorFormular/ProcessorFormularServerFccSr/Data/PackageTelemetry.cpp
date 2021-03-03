#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageTelemetry.h"

PackageTelemetry::PackageTelemetry(uint32_t msgNum,
                                   uint32_t prevMsgNum,
                                   QByteArray &array)
    : _header(Directive::DIR_152,
              msgNum,
              prevMsgNum,
              TypeInfo::INFO_2005,
              array.size(),
              CodeTicket::TICKET_00),
      _array(array)
{
}

PackageTelemetry::PackageTelemetry(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), sizeof (_data));
}

QByteArray PackageTelemetry::serialize()
{
    return prepareData(_header.serialize() + _array);
}

void PackageTelemetry::unserialize(Telemetry &telemetry)
{
    telemetry.unserialize(_data_block.telemetry);
}
