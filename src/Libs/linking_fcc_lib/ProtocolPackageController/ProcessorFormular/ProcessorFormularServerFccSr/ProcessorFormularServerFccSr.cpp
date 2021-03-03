#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/ProcessorFormularServerFccSr.h"
#include "utils/NetworkPackageUtils.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/FactoryFormularFccSr.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSpecialInformation.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageTicketSr.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSingleCommand.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageControlCommand.h"
#include "linkingFcc/infornation/Params/fcc-sr/ParamsSr.h"

ProcessorFormularServerFccSr::ProcessorFormularServerFccSr()
{

}

ProcessorFormularServerFccSr::~ProcessorFormularServerFccSr()
{

}

void ProcessorFormularServerFccSr::setFactoryFormular(QSharedPointer<IFactoryFormular> factory)
{
    _factory = factory;
}

void ProcessorFormularServerFccSr::decodeByteArray(QByteArray &array)
{
    if(!_factory)
        return;

    FactoryFormularFccSr* factory = dynamic_cast<FactoryFormularFccSr*>(_factory.data());
    ParamsSr& paramsSr = ParamsSrSingleton::getInstance();

    QByteArray unescapeArray = NetworkPackageUtils::unescapeImcomingMessage(array);
    HeaderSr header(unescapeArray);
    if(!checkIncomingMessage(header, unescapeArray))
    {
        factory->addTicket(header);
        return;
    }

    switch(header.getHeader().NFORM)
    {

    case TypeInfo::INFO_2001 :
    {
        PackageSpecialInformation packageSpecialInformation(unescapeArray);
        packageSpecialInformation.unserialize(paramsSr.getSpecialInformationSr());
        break;
    }

    case TypeInfo::INFO_2002 :
    {
        PackageSingleCommand packageSingleCommand(unescapeArray);
        packageSingleCommand.unserialize(paramsSr.getSingleCommandSr());
        break;
    }

    case TypeInfo::INFO_2003 :
    {
        PackageControlCommand packageControlCommand(unescapeArray);
        packageControlCommand.unserialize(paramsSr.getControlCommandSr());
        break;
    }

    default:
        break;
    }

    factory->addTicket(header);
}

bool ProcessorFormularServerFccSr::checkIncomingMessage(HeaderSr &header, QByteArray &array)
{
    bool icCorrectIncomingMessage{false};
    header.getHeader().Code = CodeTicket::TICKET_00;

    if(header.getHeader().NFORM > TypeInfo::INFO_2008)
        header.getHeader().Code = CodeTicket::TICKET_01;
    else if(header.getHeader().NDIR > Directive::DIR_198)
        header.getHeader().Code = CodeTicket::TICKET_03;
    else if((array.size() - sizeof (header.getHeader())) != header.getHeader().LenInfo)
        header.getHeader().Code = CodeTicket::TICKET_28;
    else
        icCorrectIncomingMessage = true;

    return icCorrectIncomingMessage;
}
