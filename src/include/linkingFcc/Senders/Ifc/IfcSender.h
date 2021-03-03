#ifndef THREADSENDERIFCT_H
#define THREADSENDERIFCT_H

/*!
    \file
    \brief Класс регулярной отправки ИФКТ в ЦУП
    \author Фуфаев Никита
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "linkingFcc/Senders/Ifc/BaseIfcSender.h"
#include "linkingFcc/infornation/Params/ParamsCMS.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/FactoryFormularFCC.h"

class IfcSender : public BaseIfcSender
{
public:
    IfcSender(QSharedPointer<IPackageController> protocolPackageController);
    ~IfcSender() {}
    /*!
     * \brief Запустить работу потока
     */
    void process() override;
};

#endif // THREADSENDERIFCT_H
