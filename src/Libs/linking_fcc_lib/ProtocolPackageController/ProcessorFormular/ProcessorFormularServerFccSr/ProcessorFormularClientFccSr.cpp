#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/ProcessorFormularClientFccSr.h"
#include "utils/NetworkPackageUtils.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/FactoryFormularFccSr.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageDoplerFrequencyOffset.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackagePropagationSignalDelay.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageTelemetry.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageFunctionControl.h"
#include "linkingFcc/infornation/Params/fcc-sr/ParamsSr.h"
#include "linkingFcc/Structs/TicketDirective.h"

#include <QDebug>
#include <QString>

void ProcessorFormularClientFccSr::setFactoryFormular(QSharedPointer<IFactoryFormular> factory)
{
    _factory = factory;
}

void ProcessorFormularClientFccSr::decodeByteArray(QByteArray &array)
{
    if(!_factory)
        return;

    QByteArray unescapeArray = NetworkPackageUtils::unescapeImcomingMessage(array);
    HeaderSr header(unescapeArray);

    ParamsSr& paramsSr = ParamsSrSingleton::getInstance();
    switch(header.getHeader().NFORM)
    {

    case TypeInfo::INFO_2005 :
    {
        PackageTelemetry packageTelemetry(unescapeArray);
        packageTelemetry.unserialize(paramsSr.getTelemetry());
        break;
    }

    case TypeInfo::INFO_2006 :
    {
        PackagePropagationSignalDelay packagePropagationSignalDelay(unescapeArray);
        packagePropagationSignalDelay.unserialize(paramsSr.getPropagationSignalDelay());
        break;
    }

    case TypeInfo::INFO_2007 :
    {
        PackageDoplerFrequencyOffset packageDoplerFrequencyOffset(unescapeArray);
        packageDoplerFrequencyOffset.unserialize(paramsSr.getDoplerFrequencyOffset());
        break;
    }

    case TypeInfo::INFO_2008 :
    {
        PackageFunctionControl packageFunctionControl(unescapeArray);
        packageFunctionControl.unserialize(paramsSr.getFunctionControlSr());
        break;
    }
    default:
        break;
    }

    if (ticketDirective.contains((int)header.getHeader().NDIR))
        qDebug() << "Получена квитанция на директиву " << (int)header.getHeader().NDIR << "с кодом - " << (int)header.getHeader().Code;
}
