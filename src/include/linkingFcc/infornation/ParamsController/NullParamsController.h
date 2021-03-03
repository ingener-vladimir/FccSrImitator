#ifndef NULLPARAMSCONTROLLER_H
#define NULLPARAMSCONTROLLER_H

#include "BaseParamsController.h"

class NullParamsController : public BaseParamsController
{
public:
    NullParamsController();
    ~NullParamsController();

    void setNewParams() override {}
};

#endif // NULLPARAMSCONTROLLER_H
