#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16CommandControl.h"

#include <QSharedPointer>

PackageDirective16CommandControl::PackageDirective16CommandControl(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), array.size());
}

void PackageDirective16CommandControl::unserialize(QSharedPointer<BaseCommandControl> commands)
{
    commands->unserializeCommand(_data_block.header.NKA, _data_block.command);
}
