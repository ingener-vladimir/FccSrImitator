#ifndef PROCESSORFORMULARSERVERFCCSR_H
#define PROCESSORFORMULARSERVERFCCSR_H

#include "interface/linkingFcc/IProcessorFormular.h"

class HeaderSr;

class ProcessorFormularServerFccSr : public IProcessorFormular
{
    QSharedPointer<IFactoryFormular> _factory{nullptr}; ///< Фабрика пакетов

public:
    ProcessorFormularServerFccSr();
    ~ProcessorFormularServerFccSr();

public:
    /*!
     * \brief Установить фабрику пакетов
     * \param factory Фабрика пакетов
     */
    void setFactoryFormular(QSharedPointer<IFactoryFormular> factory);
    /*!
     * \brief Распаковать полученный массив данных
     * \param array Массив байт
     */
    void decodeByteArray(QByteArray &array);
private:
    bool checkIncomingMessage(HeaderSr &header, QByteArray &array);
};

#endif // PROCESSORFORMULARSERVERFCCSR_H
