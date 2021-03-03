#ifndef IFACTORYFORMULAR
#define IFACTORYFORMULAR

/*!
    \file
    \brief Интерфейсный класс для создания списка пакетов для отправки по сети
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QList>
#include <QSharedPointer>
#include <QQueue>
#include <QMutexLocker>

#include "linkingFcc/Structs/TypeInformation.h"

/// Набор типов фабрик пакетов
enum class TypeFactory
{
    FCC = 0, ///< Тип ЦУП
    DUBNA,
    InnerVerA, ///< Внутренний протокол для обмена сообщениями
    NULL_TYPE,
    FCC_SR
};

class IPackage;

class IFactoryFormular
{

public:
    virtual ~IFactoryFormular() = default;
    /*!
     * \brief Получение списка формуляров для отправки по сети
     * \return Список пакетов
     */
    virtual QList<QSharedPointer<IPackage>> takeListPackage() = 0;
    /*!
     * \brief getTypeFactoryFormular получение типа фабрики
     * \return типа фабрики формуляров
     */
    virtual TypeFactory getTypeFactoryFormular() { return TypeFactory::NULL_TYPE; }

    virtual void addPackage(QByteArray&, TypeInfo) {}

};

#endif // IFACTORYFORMULAR

