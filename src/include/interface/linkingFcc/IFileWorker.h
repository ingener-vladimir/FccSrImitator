#ifndef IFILEWORKER_H
#define IFILEWORKER_H

/*!
    \file
    \brief Интерфейсный класс для работы с файлом
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QDir>

enum class TypeFileORM
{
    DISTANCE,
    ANGLES
};

class IFileWorker
{

public:
    virtual ~IFileWorker() = default;
    /*!
     * \brief Записать данные в файл
     * \param data Данные для записи
     * \return Результат выполения записи
     */
    virtual bool write(const QByteArray& data) = 0;
    /*!
     * \brief Прочитать из файла
     * \return Массив данных
     */
    virtual QByteArray read() = 0;
    /*!
     * \brief Установить имя файла
     * \param name Имя файла
     */
    virtual void setNameFile(const QString& name) = 0;
    /*!
     * \brief Получить путь к файлу
     * \return Путь
     */
    virtual const QString path() const = 0;

    virtual const QString absolutePathDir() = 0;
};

#endif // IFILEWORKER_H
