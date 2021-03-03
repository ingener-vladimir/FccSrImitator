#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageTicketSr.h"

PackageTicketSr::PackageTicketSr(HeaderSr &header,
                             uint32_t msgNumber)
    : _header(header)
{
    /// NDIRКВИТ = NDIRСООБЩ + 100 при формировании квитанции на сообщение от ЦУП
    _header.getHeader().NDIR = (Directive)((uint8_t)header.getHeader().NDIR + 100);
    _header.getHeader().NPrd = msgNumber;
    _header.getHeader().LenInfo = 0;
}

QByteArray PackageTicketSr::serialize()
{
    const QByteArray array = _header.serialize();
    return prepareData(array);
}
