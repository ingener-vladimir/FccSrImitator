#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"

Header::Header()
{
    _header.RAZD = ESCAPE;
}

Header::Header(const Directive NDIR,
               const uint32_t msgNum,
               const uint32_t prevMsgNum,
               const TypeInfo NFORM,
               const int16_t NKA,
               const int16_t NNIP_KTC,
               const uint8_t NSEANS,
               const int16_t NVITKA,
               const int16_t LenInfo,
               const CodeTicket Code)
{
    _header.RAZD = ESCAPE;
    _header.NDIR = NDIR;
    _header.NPrd = msgNum;
    _header.NPrm = prevMsgNum;
    _header.NFORM = NFORM;
    _header.NKA = NKA;
    _header.NNIP_KTC = NNIP_KTC;
    _header.NSEANS = NSEANS;
    _header.NVITKA = NVITKA;
    _header.LenInfo = LenInfo;
    _header.Code = Code;
}

Header::Header(const QByteArray & array)
{
    memcpy((char*)&_data[0], array.data(), sizeof(daq::Header));
    _header.RAZD = ESCAPE;
}

Header::Header(Header &header)
{
    _header.RAZD = header.ESCAPE;
    _header.NDIR = header.getHeader().NDIR;
    _header.NPrd = header.getHeader().NPrd;
    _header.NPrm = header.getHeader().NPrm;
    _header.NFORM = header.getHeader().NFORM;
    _header.NKA = header.getHeader().NKA;
    _header.NNIP_KTC = header.getHeader().NNIP_KTC;
    _header.NSEANS = header.getHeader().NSEANS;
    _header.NVITKA = header.getHeader().NVITKA;
    _header.LenInfo = header.lengthData();
    _header.Code = header.getHeader().Code;
}

QByteArray Header::serialize()
{
    return QByteArray ((char*)&_data[0], sizeof(daq::Header));
}

IHeader *Header::unserialize(const QByteArray &)
{
    return nullptr;
}

uint32_t Header::sizeHeader() const
{
    return sizeof(daq::Header);
}

int32_t Header::lengthData() const
{
    return _header.LenInfo;
}

daq::Header& Header::getHeader()
{
    return _header;
}

void Header::resetParamsSession()
{
    _header.NKA = 0;
    _header.NSEANS = 0;
    _header.NVITKA = 0;
}
