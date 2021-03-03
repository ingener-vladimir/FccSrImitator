#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective112Angle.h"

PackageDirective112Angle::PackageDirective112Angle(uint32_t msgNum,
                                                   Header &header,
                                                   QByteArray &array)
     : _header(header)
{
    _header.getHeader().NDIR = Directive::DIR_112;
    _header.getHeader().NPrd = msgNum;
    _header.getHeader().LenInfo = array.size();
    _header.getHeader().Code = CodeTicket::TICKET_00;

    _array = array;
}

QByteArray PackageDirective112Angle::serialize()
{
    return prepareData(QByteArray(_header.serialize() + _array));
}
