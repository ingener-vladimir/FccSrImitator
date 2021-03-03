#include "linkingFcc/Senders/Ifc/BaseIfcSender.h"

BaseIfcSender::BaseIfcSender(QSharedPointer<IPackageController> protocolPackageController)
    : _protocolPackageController(protocolPackageController)
{
    QObject::connect(&_timer, &QTimer::timeout,
                     this, &BaseIfcSender::process);

    _timer.start(TIME_SEND);
}

BaseIfcSender::~BaseIfcSender()
{
    _timer.stop();
}

void BaseIfcSender::setIsActive(bool value)
{
    isActive = value;
}


