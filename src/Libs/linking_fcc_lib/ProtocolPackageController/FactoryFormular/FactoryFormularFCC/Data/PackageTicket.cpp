#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageTicket.h"

PackageTicket::PackageTicket(Header &header,
                             uint32_t msgNumber)
    : _header(header)
{
    /// NDIRКВИТ = NDIRСООБЩ + 100 при формировании квитанции на сообщение от ЦУП
    _header.getHeader().NDIR = (Directive)((uint8_t)header.getHeader().NDIR + 100);
    _header.getHeader().NPrd = msgNumber;
    _header.getHeader().LenInfo = 0;
    _header.getHeader().NPrm = header.getHeader().NPrm;
    _header.getHeader().Code = _header.getHeader().Code;
}

QByteArray PackageTicket::serialize()
{
    const QByteArray array = _header.serialize();
    return prepareData(array);
}
