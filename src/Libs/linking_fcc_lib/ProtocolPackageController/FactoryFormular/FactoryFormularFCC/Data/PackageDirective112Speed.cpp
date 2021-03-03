#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective112Speed.h"

PackageDirective112Speed::PackageDirective112Speed(uint32_t msgNum,
                                                   QByteArray &array)
     : _header(array)
{
    _header.getHeader().NDIR = Directive::DIR_112;
    _header.getHeader().NPrd = msgNum;
    _header.getHeader().LenInfo = array.size() - sizeof(daq::Header);
    _header.getHeader().Code = CodeTicket::TICKET_00;

    memset(_data, 0, sizeof(_data));
    memcpy(_data, array.data(), array.size());
}

QByteArray PackageDirective112Speed::serialize()
{
    _data_block.structSpeed.code = CODE_SPEED;
    _data_block.headerPkg = _header.getHeader();
    return prepareData(QByteArray((char*)_data, _header.lengthData() + sizeof(daq::Header)));
}
