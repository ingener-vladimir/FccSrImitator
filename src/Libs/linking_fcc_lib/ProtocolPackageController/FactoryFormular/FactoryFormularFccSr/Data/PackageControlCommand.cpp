#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageControlCommand.h"

PackageControlCommand::PackageControlCommand(uint32_t msgNum,
                                             uint32_t prevMsgNum,
                                             QByteArray &array)
    : _header(Directive::DIR_16,
              msgNum,
              prevMsgNum,
              TypeInfo::INFO_2003,
              array.size(),
              CodeTicket::TICKET_00),
      _array(array)
{

}

PackageControlCommand::PackageControlCommand(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), array.size());
}

QByteArray PackageControlCommand::serialize()
{
    return prepareData(_header.serialize() + _array);
}

void PackageControlCommand::unserialize(ControlCommandSr &controlCommandSr)
{
    controlCommandSr.unserialize(_data_block.structControlCommand);
}
