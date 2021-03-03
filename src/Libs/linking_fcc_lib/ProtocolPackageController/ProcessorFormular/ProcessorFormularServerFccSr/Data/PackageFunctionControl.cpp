#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageFunctionControl.h"

PackageFunctionControl::PackageFunctionControl(uint32_t msgNum,
                                               uint32_t prevMsgNum,
                                               QByteArray array)
    : _header(Directive::DIR_155,
              msgNum,
              prevMsgNum,
              TypeInfo::INFO_2008,
              array.size(),
              CodeTicket::TICKET_00),
      _array(array)
{
}

PackageFunctionControl::PackageFunctionControl(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), sizeof (_data));
}

QByteArray PackageFunctionControl::serialize()
{
    return prepareData(_header.serialize() + _array);
}

void PackageFunctionControl::unserialize(FunctionControlSr &functionControlSr)
{
    functionControlSr.unserialize(_data_block.control);
}
