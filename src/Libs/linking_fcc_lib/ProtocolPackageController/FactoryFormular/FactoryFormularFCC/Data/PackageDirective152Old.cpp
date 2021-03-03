#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective152Old.h"

PackageDirective152Old::PackageDirective152Old(uint32_t msgNum, const QByteArray& array)
    : _header(array)
{
    _header.getHeader().NDIR = Directive::DIR_152;
    _header.getHeader().NPrd = msgNum;
    _header.getHeader().NFORM = TypeInfo::INFO_1888;
    _header.getHeader().LenInfo = sizeof(PD152Old);

    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), std::min(sizeof(_data), size_t(array.size())));
}

QByteArray PackageDirective152Old::serialize()
{
    _data_block.headerPkg = _header.getHeader();
    return prepareData(QByteArray((char*)_data, sizeof(_data)));
}

