#ifndef FILEWORKERTD_H
#define FILEWORKERTD_H

/*!
    \file
    \brief Класс-наследник работы с файлами ЦУ
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include <QRegularExpression>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

#include "BaseFileWorker.h"

class FileWorkerTD : public BaseFileWorker
{
    const QString dirInternal = "/internal/";
    const QString dirTD = "/TD/";
    const QString pathOutTD = "/out/TD/";
    const QString expansion = ".cu";
    QByteArray inputLineTerminator = QByteArrayLiteral("\r\n");
    const QString formatDateTime{"dd/MM/yyyy | hh:mm:ss"};

public:
    FileWorkerTD();
    ~FileWorkerTD() {}
    /*!
     * \brief Записать данные в файл
     * \param data Данные для записи
     * \return Результат выполения записи
     */
    bool write(const QByteArray& data) override;

private:
    /*!
     * \brief Преобразовать данные по ЦУ в формат json
     * \param array Данные ЦУ
     * \return Массив в формате json
     */
    QByteArray getDataFormatJson(const QByteArray &array);
    /*!
     * \brief Разобрать строку из файла ЦУ и записать в QJsonObject
     * \param line Строка
     * \return QJsonObject строки
     */
    QJsonObject parseLineTD(const QByteArray &line);
};

#endif // FILEWORKERTD_H
