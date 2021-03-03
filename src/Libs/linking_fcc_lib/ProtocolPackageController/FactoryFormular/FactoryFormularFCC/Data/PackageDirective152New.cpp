#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective152New.h"

PackageDirective152New::PackageDirective152New(uint32_t msgNum,
                                               const QByteArray& array)
    : _header(array)
{
    _header.getHeader().NDIR = Directive::DIR_152;
    _header.getHeader().NPrd = msgNum;
    _header.getHeader().NFORM = TypeInfo::INFO_1888;
    _header.getHeader().LenInfo = sizeof(PD152New);

    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), std::min(sizeof(_data), size_t(array.size())));
}

QByteArray PackageDirective152New::serialize()
{
    _data_block.headerPkg = _header.getHeader();
    return prepareData(QByteArray((char*)_data, sizeof(_data)));
}

