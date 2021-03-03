#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h"

HeaderSr::HeaderSr()
{
    _header.RAZD = ESCAPE;
}

HeaderSr::HeaderSr(const Directive NDIR,
               const uint32_t msgNum,
               const uint32_t prevMsgNum,
               const TypeInfo NFORM,
               const int16_t LenInfo,
               const CodeTicket Code)
{
    _header.RAZD = ESCAPE;
    _header.NDIR = NDIR;
    _header.NPrd = msgNum;
    _header.NPrm = prevMsgNum;
    _header.NFORM = NFORM;
    _header.LenInfo = LenInfo;
    _header.Code = Code;
}

HeaderSr::HeaderSr(const QByteArray & array)
{
    memcpy((char*)&_data[0], array.data(), sizeof(sr::HeaderSr));
    _header.RAZD = ESCAPE;
}

HeaderSr::HeaderSr(HeaderSr &header)
{
    _header.RAZD = header.ESCAPE;
    _header.NDIR = header.getHeader().NDIR;
    _header.NPrd = header.getHeader().NPrd;
    _header.NPrm = header.getHeader().NPrm;
    _header.NFORM = header.getHeader().NFORM;
    _header.LenInfo = header.lengthData();
    _header.Code = header.getHeader().Code;
}

QByteArray HeaderSr::serialize()
{
    return QByteArray ((char*)&_data[0], sizeof(sr::HeaderSr));
}

IHeader *HeaderSr::unserialize(const QByteArray &)
{
    return nullptr;
}

uint32_t HeaderSr::sizeHeader() const
{
    return sizeof(sr::HeaderSr);
}

int32_t HeaderSr::lengthData() const
{
    return _header.LenInfo;
}

sr::HeaderSr& HeaderSr::getHeader()
{
    return _header;
}
