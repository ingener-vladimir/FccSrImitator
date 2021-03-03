#ifndef BASEFILEWORKER_H
#define BASEFILEWORKER_H

/*!
    \file
    \brief Класс-наследник, имплементирующий функции работы с файлами
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "interface/linkingFcc/IFileWorker.h"

class BaseFileWorker : public IFileWorker
{

public:
    BaseFileWorker();
    ~BaseFileWorker();
    /*!
     * \brief Установить имя файла
     * \param name Имя файла
     */
    void setNameFile(const QString& name) override;
    /*!
     * \brief Получить путь к файлу
     * \return Путь
     */
    const QString path() const override;
    /*!
     * \brief Прочитать из файла
     * \return Массив данных
     */
    QByteArray read() override;
    /*!
     * \brief Получить абсолютный путь директории с файлом
     * \return Путь
     */
    const QString absolutePathDir() override;

protected:
    QFile file;
    const QString pathFiles{"../../../data/"};
    QString filePath{""};
    QDir dir;
};

#endif // BASEFILEWORKER_H
