#ifndef PARAMSCONTROLLER649_H
#define PARAMSCONTROLLER649_H

#include "BaseParamsController.h"

class ParamsController649 : public BaseParamsController
{
public:
    ParamsController649() {}
    ~ParamsController649() {}
    /*!
     * \brief Установить новые параметры
     */
    void setNewParams() override;
};

#endif // PARAMSCONTROLLER649_H
