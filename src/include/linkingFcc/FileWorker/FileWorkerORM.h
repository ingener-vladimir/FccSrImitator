#ifndef FILEWORKERORM_H
#define FILEWORKERORM_H

/*!
    \file
    \brief Класс-наследник работы с файлами РКО
    \author Саньков Владимир
    \version 0.1
    \date декабрь 2019 г.
*/

#include "BaseFileWorker.h"

class FileWorkerORM : public BaseFileWorker
{
    const QString dirOut = "/out/";
    const QString dirDist = "/distance/";
    const QString dirAng = "/angles/";

public:
    FileWorkerORM(TypeFileORM type);

    /*!
     * \brief Записать данные в файл
     * \param data Данные для записи
     * \return Результат выполения записи
     */
    bool write(const QByteArray& data) override;
};

#endif // FILEWORKERORM_H
