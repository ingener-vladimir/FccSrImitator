#include "linkingFcc/ProtocolPackageController/ProtocolPackageController.h"

ProtocolPackageController::ProtocolPackageController(QSharedPointer<IFactoryFormular> factory,
                                                     QSharedPointer<IProcessorFormular> processor) :
    _factory(factory),
    _processor(processor)
{
    _processor->setFactoryFormular(_factory);
}

ProtocolPackageController::ProtocolPackageController(TypeFactory typeFactory, QSharedPointer<GUIExchangeAdapter> _guiExchangeAdapter)
{
    //инициалищация процессора и фабрики пакетов
    _processor = ProcessorFormular::createProcessorFormularServer(typeFactory, _guiExchangeAdapter);
    _factory = FactoryFormular::createFactoryFormular(typeFactory);
    _processor->setFactoryFormular(_factory);
}

ProtocolPackageController::~ProtocolPackageController()
{
    _factory.reset();
    _factory = nullptr;
    _processor.reset();
    _processor = nullptr;
}

QList<QByteArray> ProtocolPackageController::getPackageList()
{
    if(!_factory)
        return QList<QByteArray>();

    QList<QSharedPointer<IPackage>> pack = _factory->takeListPackage();
    QList<QByteArray> list;
    for(auto & iter : pack)
    {
        list.append(iter->serialize());
        iter.clear();
    }
    return list;
}

void ProtocolPackageController::appendPackage(QByteArray &array)
{
    if(!_processor)
        return;

    _processor->decodeByteArray(array);
}

QSharedPointer<IFactoryFormular> ProtocolPackageController::getFactory()
{
    return _factory;
}

QSharedPointer<IProcessorFormular> ProtocolPackageController::getProcessor()
{
    return _processor;
}
