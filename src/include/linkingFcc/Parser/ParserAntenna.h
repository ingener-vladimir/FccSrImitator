#ifndef PARSERANTENNA_H
#define PARSERANTENNA_H

/*!
    \file
    \brief Класс-наследник, реализующий парсинг параметров от Антенны
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "BaseParser.h"
#include "linkingFcc/FileWorker/FileWorkerORM.h"

class ParserAntenna : public BaseParser
{
    ///< Структура для хранения значений угловых измерений
    struct Chunk
    {
        double el;   ///< угол места
        double az;   ///< азимут
        QDateTime t; ///< время регистрации измерения

        QString toString(int kis);
    };

    int _currentNumber{-1};       ///< последний номер измерения
    QDateTime _timeStart;         ///< время начала измерений
    QDateTime _timeStop;          ///< время окончания измерени
    QVector<Chunk> _vectorAngles; ///< вектор измерений за сеанс

    const QString EXPANSION_LMF = ".LMF";
    const QString EXPANSION_UG = ".ug";
    const QString SEPARATOR = "_";

public:
    ParserAntenna(QSharedPointer<IJournal> journal = nullptr);
    ~ParserAntenna() {}
    /*!
     * \brief Распарсить полученные данные
     * \param params Все параметры
     * \param obj Json с данными от устройства
     */
    void parseParams(const QJsonObject& obj) override;

private:
    /*!
     * \brief Записать значения угловых измерений в файл
     * \param params Параметры
     */
    void writeParamsAngles();
    /*!
     * \brief Сгенерировать заголовок файла с УМ
     * \param ka Номер КА
     * \return Заголовок
     */
    QString genHeader(const int16_t ka);
    /*!
     * \brief Записать данные УМ в бинарный файл
     * \param params Параметры
     * \param ba Массив данных
     */
    void flushBinaryFile(QByteArray ba);
};

#endif // PARSERANTENNA_H
