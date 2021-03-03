#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16OneTimeCommand.h"

PackageDirective16OneTimeCommand::PackageDirective16OneTimeCommand(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), array.size());
}

void PackageDirective16OneTimeCommand::unserialize(SingleCommand &commands)
{
    commands.unserializeCommand(_data_block.oneTimeCommand);
}
