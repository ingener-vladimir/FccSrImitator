#ifndef IPACKAGECONTROLLER
#define IPACKAGECONTROLLER

/*!
    \file
    \brief Интерфейсный класс для делегтрования задач отправки и распаковки полученных пакетов
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QList>
#include <QByteArray>
#include <QSharedPointer>

class IFactoryFormular;
class IProcessorFormular;
class IPackage;

class IPackageController
{

public:
    virtual ~IPackageController() = default;
    /*!
     * \brief Получить список пакетов для отправки
     * \return Список пакетов
     */
    virtual QList<QByteArray> getPackageList() = 0;
    /*!
     * \brief Передать полученные пакеты для распаковки
     * \param array Массив данных
     */
    virtual void appendPackage(QByteArray& array) = 0;
    /*!
     * \brief Вернуть указатель типа фабрики
     * \return Указатель
     */
    virtual QSharedPointer<IFactoryFormular> getFactory() = 0;
    /*!
     * \brief Вернуть указатель типа процессора
     * \return Указатель
     */
    virtual QSharedPointer<IProcessorFormular> getProcessor() = 0;
};

#endif // IPACKAGECONTROLLER

