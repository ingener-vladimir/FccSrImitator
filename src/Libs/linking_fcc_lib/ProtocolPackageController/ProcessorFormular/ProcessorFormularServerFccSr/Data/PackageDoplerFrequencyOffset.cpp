#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageDoplerFrequencyOffset.h"

PackageDoplerFrequencyOffset::PackageDoplerFrequencyOffset(uint32_t msgNum,
                                                           uint32_t prevMsgNum,
                                                           QByteArray &array)
    : _header(Directive::DIR_153,
              msgNum,
              prevMsgNum,
              TypeInfo::INFO_2007,
              array.size(),
              CodeTicket::TICKET_00),
      _array(array)
{
}

PackageDoplerFrequencyOffset::PackageDoplerFrequencyOffset(QByteArray &array)
{
    _array = array.mid(sizeof (sr::HeaderSr));
}

QByteArray PackageDoplerFrequencyOffset::serialize()
{
    return prepareData(_header.serialize() + _array);
}

void PackageDoplerFrequencyOffset::unserialize(DoplerFrequencyOffset& doplerFrequencyOffset)
{
    doplerFrequencyOffset.unserialize(_array);
}
