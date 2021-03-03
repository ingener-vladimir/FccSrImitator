#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective25.h"

PackageDirective25::PackageDirective25(QByteArray &array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), sizeof(_data));
}

void PackageDirective25::unserialize(QByteArray&)
{

}
