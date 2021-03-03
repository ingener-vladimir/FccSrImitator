#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective12.h"

PackageDirective12::PackageDirective12(QByteArray &array)
    : _header(array)
{
    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), array.size());
}

uint16_t PackageDirective12::getData() const
{
    return _data_block.bandTLM.date;
}

uint32_t PackageDirective12::getTime() const
{
    return _data_block.bandTLM.time;
}

