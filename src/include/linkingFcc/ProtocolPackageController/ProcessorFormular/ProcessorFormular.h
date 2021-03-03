#ifndef PROCESSORFORMULAR_H
#define PROCESSORFORMULAR_H

/*!
    \file
    \brief Класс для создания объекта процессора пакетов в зависимости от типа процессора
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/ProcessorFormularServer.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/ProcessorFormularServerFccSr.h"
#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/ProcessorFormularClientFccSr.h"

class ProcessorFormular
{
public:
    /*!
     * \brief Конструктор
     * \param type Тип процессора
     */
    ProcessorFormular() = delete;
    ~ProcessorFormular() = delete;
public:
    static QSharedPointer<IProcessorFormular> createProcessorFormularClient(TypeFactory type);
    static QSharedPointer<IProcessorFormular> createProcessorFormularServer(TypeFactory type,
                                                                            QSharedPointer<GUIExchangeAdapter> _guiExchangeAdapter = nullptr);

};

#endif // PROCESSORFORMULAR_H
