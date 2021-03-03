#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormular.h"

QSharedPointer<IProcessorFormular> ProcessorFormular::createProcessorFormularServer(TypeFactory type, QSharedPointer<GUIExchangeAdapter> _guiExchangeAdapter)
{
    if(type == TypeFactory::FCC)
        return QSharedPointer<IProcessorFormular>(new ProcessorFormularServer(_guiExchangeAdapter));

    else if(type == TypeFactory::FCC_SR)
        return QSharedPointer<IProcessorFormular>(new ProcessorFormularServerFccSr());

    return QSharedPointer<IProcessorFormular>();
}


QSharedPointer<IProcessorFormular> ProcessorFormular::createProcessorFormularClient(TypeFactory type)
{
    //    реализовать ProcessorFormularClient для клиента
    if(type == TypeFactory::FCC_SR)
        return  QSharedPointer<IProcessorFormular>(new ProcessorFormularClientFccSr());

    return QSharedPointer<IProcessorFormular>();
}
