#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16SpecialInfo.h"

PackageDirective16SpecialInfo::PackageDirective16SpecialInfo(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), array.size());
}

void PackageDirective16SpecialInfo::unserialize(QByteArray&)
{

}
