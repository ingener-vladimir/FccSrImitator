#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective98.h"

PackageDirective98::PackageDirective98(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), sizeof(_data));
}

void PackageDirective98::unserialize(QByteArray&)
{

}
