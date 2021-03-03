#ifndef PROCESSORFORMULARCLIENTFCCSR_H
#define PROCESSORFORMULARCLIENTFCCSR_H

#include "interface/linkingFcc/IProcessorFormular.h"

class ProcessorFormularClientFccSr : public IProcessorFormular
{
    QSharedPointer<IFactoryFormular> _factory{nullptr}; ///< Фабрика пакетов
public:
    ProcessorFormularClientFccSr() {}
    ~ProcessorFormularClientFccSr() {}

public:
    /*!
     * \brief Установить фабрику пакетов
     * \param factory Фабрика пакетов
     */
    void setFactoryFormular(QSharedPointer<IFactoryFormular> factory) override;
    /*!
     * \brief Распаковать полученный массив данных
     * \param array Массив байт
     */
    void decodeByteArray(QByteArray &array) override;
};

#endif // PROCESSORFORMULARCLIENTFCCSR_H
