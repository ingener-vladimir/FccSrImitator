#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective198.h"

PackageDirective198::PackageDirective198(uint32_t msgNum,
                                         Header &header,
                                         QByteArray &array)
    : _header(header)
{
    _header.getHeader().NDIR = Directive::DIR_198;
    _header.getHeader().NPrd = msgNum;
    _header.getHeader().LenInfo = array.size();
    _header.getHeader().Code = CodeTicket::TICKET_00;

    _array = array;
}

QByteArray PackageDirective198::serialize()
{
    return prepareData(_header.serialize() + _array);
}
