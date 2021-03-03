#ifndef BASEIFCSENDER_H
#define BASEIFCSENDER_H

#include "interface/linkingFcc/IIfcSender.h"
#include "interface/linkingFcc/IPackageController.h"

#include <QTimer>

class BaseIfcSender : public IIfcSender
{
    QTimer _timer;                       ///< Таймер отправки
    static const uint16_t TIME_SEND = 1000;
public:
    BaseIfcSender(QSharedPointer<IPackageController> protocolPackageController);
    virtual ~BaseIfcSender();

    void setIsActive(bool value) override;
    inline bool getIsActive() const override { return isActive; }
protected:
    QSharedPointer<IPackageController> _protocolPackageController{nullptr};
    bool isActive{false};
};

#endif // BASEIFCSENDER_H
