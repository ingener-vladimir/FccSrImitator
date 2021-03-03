#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSingleCommand.h"

PackageSingleCommand::PackageSingleCommand(uint32_t msgNum,
                                           uint32_t prevMsgNum,
                                           QByteArray& array)
    : _header(Directive::DIR_16,
              msgNum,
              prevMsgNum,
              TypeInfo::INFO_2002,
              array.size(),
              CodeTicket::TICKET_00),
      _array(array)
{

}

PackageSingleCommand::PackageSingleCommand(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), sizeof (_data));
}

QByteArray PackageSingleCommand::serialize()
{
    return prepareData(_header.serialize() + _array);
}

void PackageSingleCommand::unserialize(SingleCommandSr &singleCommandSr)
{
    singleCommandSr.unserialize(_data_block.structSingleCommand);
}
