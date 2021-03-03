#include "linkingFcc/infornation/ParamsController/FactoryParamsController.h"

FactoryParamsController::FactoryParamsController(const int16_t nip)
{
    switch (nip)
    {

    case 512:
    case 711:
    case 725:
    case 811:
    {
        _controller = QSharedPointer<ParamsController>(new ParamsController());
        break;
    }

    case 649:
    {
        _controller = QSharedPointer<ParamsController649>(new ParamsController649());
        break;
    }

    default:
    {
        _controller = QSharedPointer<NullParamsController>(new NullParamsController());
        break;
    }

    }
}

FactoryParamsController::~FactoryParamsController()
{
    _controller.reset();
    _controller = nullptr;
}

QSharedPointer<IParamsController> FactoryParamsController::getParamsController() const
{
    return _controller;
}
