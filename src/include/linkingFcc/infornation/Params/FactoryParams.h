#ifndef FACTORYPARAMS_H
#define FACTORYPARAMS_H

#include "linkingFcc/infornation/Params/ParamsCMS.h"
#include "linkingFcc/Singleton/Singleton.h"
#include "linkingFcc/infornation//FunctionControl/InfoFunctionControl.h"
#include "linkingFcc/infornation//FunctionControl/FunctionControl649.h"
#include "linkingFcc/infornation//FunctionControl/FunctionControl330.h"
#include "linkingFcc/infornation//FunctionControl/FunctionControl344.h"
#include "linkingFcc/infornation//FunctionControl/FunctionControl345.h"
#include "linkingFcc/infornation//FunctionControl/FunctionControl346.h"
#include "linkingFcc/infornation//CommandControl/CommandControl.h"
#include "linkingFcc/infornation//CommandControl/CommandControl649.h"
#include "linkingFcc/infornation//ParamsController/ParamsController.h"
#include "linkingFcc/infornation//ParamsController/ParamsController649.h"

class FactoryParamsCMS
{
    ParamsCMS& params = ParamsSingleton::getInstance();

    QSharedPointer<BaseParamsController> _paramsController{nullptr};
    QSharedPointer<BaseFunctionControl> _functionControl{nullptr};
    QSharedPointer<BaseCommandControl> _commandControl{nullptr};

public:
    FactoryParamsCMS();
    void createParamsCMS(const uint16_t ka, StructFunctionControl *control);

    QSharedPointer<BaseParamsController> paramsController() const;

private:
    void setCommonParams();
};

#endif // FACTORYPARAMS_H
