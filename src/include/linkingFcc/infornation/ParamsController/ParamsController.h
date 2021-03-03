#ifndef PARAMSCONTROLLER_H
#define PARAMSCONTROLLER_H

/*!
    \file
    \brief Класс контроля параметров станции
    \author Саньков Владимир
    \version 0.1
    \date декабрь 2019 г.
*/

#include "BaseParamsController.h"

class ParamsController : public BaseParamsController
{

public:
    ParamsController() {}
    ~ParamsController() {}

    /*!
     * \brief Установить новые параметры
     */
    void setNewParams() override;
};

#endif // PARAMSCONTROLLER_H
