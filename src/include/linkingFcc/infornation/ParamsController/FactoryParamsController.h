#ifndef FACTORYPARAMSCONTROLLER_H
#define FACTORYPARAMSCONTROLLER_H

#include "ParamsController649.h"
#include "ParamsController.h"
#include "NullParamsController.h"

class FactoryParamsController
{
    QSharedPointer<IParamsController> _controller{nullptr};

public:
    FactoryParamsController(const int16_t nip);
    ~FactoryParamsController();

    QSharedPointer<IParamsController> getParamsController() const;
};

#endif // FACTORYPARAMSCONTROLLER_H
