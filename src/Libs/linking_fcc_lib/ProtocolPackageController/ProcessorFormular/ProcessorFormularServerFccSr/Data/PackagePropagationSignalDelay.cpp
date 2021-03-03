#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackagePropagationSignalDelay.h"

PackagePropagationSignalDelay::PackagePropagationSignalDelay(uint32_t msgNum,
                                                             uint32_t prevMsgNum,
                                                             QByteArray &array)
    : _header(Directive::DIR_153,
              msgNum,
              prevMsgNum,
              TypeInfo::INFO_2006,
              array.size(),
              CodeTicket::TICKET_00),
      _array(array)
{
}

PackagePropagationSignalDelay::PackagePropagationSignalDelay(QByteArray &array)
{
    _array = array.mid(sizeof (sr::HeaderSr));
}

QByteArray PackagePropagationSignalDelay::serialize()
{
    return prepareData(_header.serialize() + _array);
}

void PackagePropagationSignalDelay::unserialize(PropagationSignalDelay &propagationSignalDelay)
{
    propagationSignalDelay.unserialize(_array);
}
