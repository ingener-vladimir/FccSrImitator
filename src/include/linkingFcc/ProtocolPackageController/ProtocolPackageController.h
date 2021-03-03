#ifndef TCPPACKAGECONTROLLER_H
#define TCPPACKAGECONTROLLER_H

#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormular.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormular.h"
#include "interface/linkingFcc/IPackageController.h"
#include "interface/linkingFcc/IPackage.h"

class ProtocolPackageController : public IPackageController
{
    QSharedPointer<IFactoryFormular> _factory{nullptr};
    QSharedPointer<IProcessorFormular> _processor{nullptr};

public:
    ProtocolPackageController(QSharedPointer<IFactoryFormular> factory,
                         QSharedPointer<IProcessorFormular> processor);
    ProtocolPackageController(TypeFactory typeFactory, QSharedPointer<GUIExchangeAdapter> _guiExchangeAdapter = nullptr);

    ~ProtocolPackageController();

    QList<QByteArray> getPackageList() override;
    void appendPackage(QByteArray& array) override;

    QSharedPointer<IFactoryFormular> getFactory() override;
    QSharedPointer<IProcessorFormular> getProcessor() override;

};

#endif // TCPPACKAGECONTROLLER_H
