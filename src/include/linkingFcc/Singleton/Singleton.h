#ifndef SINGLETON_H
#define SINGLETON_H

/*!
    \file
    \brief Класс, реализующий паттерн Синглтон(многопоточный)
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QMutexLocker>

static QMutex _mutex; ///< Глобальный мьютекс

template <class T>
class Singleton
{

public:
    /*!
     * \brief Небезопасная функция в многопоточном окружении
     * \return Указатель на объект типа Т
     */
    static T* getInstanceUnsafe()
    {
        static T instance;
        return &instance;
    }
    /*!
     * \brief Функция для использования в многопоточном окружении
     * \return Ссылка на объект типа Т
     */
    static T& getInstance()
    {
        static T* volatile pt;
        if (!pt)
        {
            T* tmp;
            {
                QMutexLocker lock(&_mutex);
                tmp = getInstanceUnsafe();
            }
            pt = tmp;
        }
        return *pt;
    }

    /// Запрет вызова конструктора
    Singleton() = delete;
    /// Запрет вызова деструктора
    ~Singleton() = delete;
    /// Запрет вызова конструктора копирования
    Singleton(const Singleton &) = delete;
    /// Запрет вызова оператора присваивания
    Singleton& operator=(const Singleton &) = delete;
};

#endif // SINGLETON_H
