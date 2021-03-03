#ifndef FACTORYFORMULARFCCSR_H
#define FACTORYFORMULARFCCSR_H

#include "interface/linkingFcc/IFactoryFormular.h"

class HeaderSr;

class FactoryFormularFccSr : public IFactoryFormular
{
    QMutex _mutex;                              ///< Мюьтек для синхронизации работы со списком пакетов
    uint32_t _msg_num{1};                       ///< Номер текущего сообщения
    uint32_t _lastMessageNumber{0};             ///< Номер последнего принятого сообщения
    QList<QSharedPointer<IPackage>> _list_pack; ///< Список пакетов для отправки

    /*!
     * \brief Получить номер следующего сообщения
     * \return Номер сообщения
     */
    uint32_t getMessageNumber();
public:
    FactoryFormularFccSr() {}
    ~FactoryFormularFccSr() {}

    // IFactoryFormular interface
public:
    QList<QSharedPointer<IPackage> > takeListPackage() override;
    TypeFactory getTypeFactoryFormular() override;
    void addPackage(QByteArray &array, TypeInfo typeInfo) override;

    void addTicket(HeaderSr& header);
    void addPackageControlCommand(QByteArray &array);
    void addPackageSingleCommand(QByteArray &array);
    void addPackageSpecialInformation(QByteArray &array);
    void addPackageDoplerFrequencyOffset(QByteArray &array);
    void addPackageFunctionControl(QByteArray array);
    void addPackagePropagationSignalDelay(QByteArray &array);
    void addPackageTelemetry(QByteArray &array);

    void setLastMessageNumber(const uint32_t &lastMessageNumber);
};

#endif // FACTORYFORMULARFCCSR_H
