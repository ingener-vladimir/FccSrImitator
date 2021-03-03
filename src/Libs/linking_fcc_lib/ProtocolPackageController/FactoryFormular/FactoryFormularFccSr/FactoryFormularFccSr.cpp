#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/FactoryFormularFccSr.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageTicketSr.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSpecialInformation.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSingleCommand.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageControlCommand.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageDoplerFrequencyOffset.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackagePropagationSignalDelay.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageTelemetry.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageFunctionControl.h"

QList<QSharedPointer<IPackage> > FactoryFormularFccSr::takeListPackage()
{
    QMutexLocker lock(&_mutex);
    QList<QSharedPointer<IPackage>> pack(_list_pack);
    _list_pack.clear();
    return pack;
}

TypeFactory FactoryFormularFccSr::getTypeFactoryFormular()
{
    return TypeFactory::FCC_SR;
}

void FactoryFormularFccSr::addTicket(HeaderSr& header)
{
    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageTicketSr(header, getMessageNumber())));
}

void FactoryFormularFccSr::addPackageControlCommand(QByteArray& array)
{
    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageControlCommand(getMessageNumber(),
                                                                         _lastMessageNumber,
                                                                         array)));
}

void FactoryFormularFccSr::addPackageSingleCommand(QByteArray& array)
{
    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageSingleCommand(getMessageNumber(),
                                                                        _lastMessageNumber,
                                                                        array)));
}

void FactoryFormularFccSr::addPackageSpecialInformation(QByteArray& array)
{
    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageSpecialInformation(getMessageNumber(),
                                                                             _lastMessageNumber,
                                                                             array)));
}

void FactoryFormularFccSr::addPackageDoplerFrequencyOffset(QByteArray& array)
{
    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageDoplerFrequencyOffset(getMessageNumber(),
                                                                                _lastMessageNumber,
                                                                                array)));
}

void FactoryFormularFccSr::addPackageFunctionControl(QByteArray array)
{
    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageFunctionControl(getMessageNumber(),
                                                                          _lastMessageNumber,
                                                                          array)));
}

void FactoryFormularFccSr::addPackagePropagationSignalDelay(QByteArray& array)
{
    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackagePropagationSignalDelay(getMessageNumber(),
                                                                                 _lastMessageNumber,
                                                                                 array)));
}

void FactoryFormularFccSr::addPackageTelemetry(QByteArray& array)
{
    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageTelemetry(getMessageNumber(),
                                                                    _lastMessageNumber,
                                                                    array)));
}

void FactoryFormularFccSr::setLastMessageNumber(const uint32_t &lastMessageNumber)
{
    _lastMessageNumber = lastMessageNumber;
}

uint32_t FactoryFormularFccSr::getMessageNumber()
{
    return (_msg_num == 0) ? _msg_num = 1 : _msg_num++;
}


void FactoryFormularFccSr::addPackage(QByteArray &array, TypeInfo typeInfo)
{
    switch (typeInfo)
    {
    case TypeInfo::INFO_2001:
    {
        addPackageSpecialInformation(array);
        break;
    }
    case TypeInfo::INFO_2002:
    {
        addPackageSingleCommand(array);
        break;
    }
    case TypeInfo::INFO_2003:
    {
        addPackageControlCommand(array);
        break;
    }
    }
}
