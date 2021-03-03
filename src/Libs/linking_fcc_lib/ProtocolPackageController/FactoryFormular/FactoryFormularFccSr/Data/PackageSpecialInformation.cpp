#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSpecialInformation.h"

PackageSpecialInformation::PackageSpecialInformation(uint32_t msgNum, uint32_t prevMsgNum, QByteArray &array)
    : _header(Directive::DIR_16,
              msgNum,
              prevMsgNum,
              TypeInfo::INFO_2001,
              array.size(),
              CodeTicket::TICKET_00),
      _array(array)
{

}

PackageSpecialInformation::PackageSpecialInformation(QByteArray &array)
{
    _array = array.mid(sizeof (sr::HeaderSr));
}

QByteArray PackageSpecialInformation::serialize()
{
    return prepareData(_header.serialize() + _array);
}

void PackageSpecialInformation::unserialize(SpecialInformationSr &specialInformationSr)
{
    specialInformationSr.unserialize(_array);
}
