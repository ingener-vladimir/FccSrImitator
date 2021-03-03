#ifndef FILEWORKERSI_H
#define FILEWORKERSI_H

/*!
    \file
    \brief Класс-наследник работы с файлами СИ
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "BaseFileWorker.h"

class FileWorkerSI : public BaseFileWorker
{
    const QString dirInternal = "/internal/";
    const QString dirSI = "/SI/";
    const QString nameFileSI = "FileSI.bit";

public:
    FileWorkerSI();

    /*!
     * \brief Записать данные в файл
     * \param data Данные для записи
     * \return Результат выполения записи
     */
    bool write(const QByteArray& data) override;
};

#endif // FILEWORKERSI_H
