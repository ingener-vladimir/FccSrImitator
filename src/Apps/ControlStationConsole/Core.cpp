#include "Core.h"
#include "linkingFcc/infornation/Params/fcc-sr/ParamsSr.h"

Core::Core()
{
    _linkingFCC.createServer(9090, TypeFactory::FCC_SR);

    QObject::connect(&_timer, &QTimer::timeout,
                     this, &Core::update);

    _timer.start(1000);
}

Core::~Core()
{
    _timer.stop();
}

void Core::update()
{
    ParamsSr& paramsSr = ParamsSrSingleton::getInstance();
    paramsSr.getFunctionControlSr().setCounterTelemetry(rand() % 100);
    paramsSr.getFunctionControlSr().setBandReceiver(rand() % 100);
    paramsSr.getFunctionControlSr().setLiter(rand() % 100);
    paramsSr.getFunctionControlSr().setLiterOTC(rand() % 100);
    paramsSr.getFunctionControlSr().setLiterPNS(rand() % 100);
}
