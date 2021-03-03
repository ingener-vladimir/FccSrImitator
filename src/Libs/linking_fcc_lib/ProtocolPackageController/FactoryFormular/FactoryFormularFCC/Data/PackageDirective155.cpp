#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective155.h"

#include <QDebug>
#include <QDateTime>

PackageDirective155::PackageDirective155(uint32_t msgNum,
                                         QByteArray& array)
    : _header(array)
{
    _header.getHeader().NDIR = Directive::DIR_155;
    _header.getHeader().NPrd = msgNum;
    _header.getHeader().NFORM = TypeInfo::INFO_1602;
    _header.getHeader().LenInfo = sizeof(FunctionControl);

    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), sizeof(_data));
}

QByteArray PackageDirective155::serialize()
{
    _data_block.headerPkg = _header.getHeader();
    return prepareData(QByteArray((char*)_data, sizeof(_data)));
}
