#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormular.h"


QSharedPointer<IFactoryFormular> FactoryFormular::createFactoryFormular(TypeFactory type)
{
    if(type == TypeFactory::FCC)
        return  QSharedPointer<IFactoryFormular>(new FactoryFormularFCC());

    if(type == TypeFactory::FCC_SR)
        return  QSharedPointer<IFactoryFormular>(new FactoryFormularFccSr());

    return QSharedPointer<IFactoryFormular>();
}
