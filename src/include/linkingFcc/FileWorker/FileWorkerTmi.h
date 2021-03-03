#ifndef FILEWORKERTMI_H
#define FILEWORKERTMI_H
/*!
    \file
    \brief Класс-наследник работы с файлами ТМИ
    \author Саньков Владимир
    \version 0.1
    \date январь 2020 г.
*/

#include "BaseFileWorker.h"

class FileWorkerTmi : public BaseFileWorker
{
    const QString dirOut = "/out/";
    const QString dirTmi = "/tmi/";

public:
    FileWorkerTmi();
    ~FileWorkerTmi() {}
    /*!
     * \brief Записать данные в файл
     * \param data Данные для записи
     * \return Результат выполения записи
     */
    bool write(const QByteArray& data) override;
};

#endif // FILEWORKERTMI_H
