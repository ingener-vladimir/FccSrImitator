#ifndef PARSERMODEM_H
#define PARSERMODEM_H

/*!
    \file
    \brief Класс-наследник, реализующий парсинг параметров от Модема
    \author Саньков Владимир
    \version 0.1
    \date ноябрь 2019 г.
*/

#include "BaseParser.h"
#include "linkingFcc/FileWorker/FileWorkerORM.h"

class ParserModem : public BaseParser
{
    uint64_t _startTime{0};       ///< Время начала приема данных РКО

    int _lastSIState{0};          ///< Последнее состояние СИ
    int32_t _currentInterval{-1}; ///< Текущий номер измерения

    const QString expansion = ".r0";
    const QString separator = "_";

    uint32_t _rkFrameN = 65499;
    uint32_t _orkFrameN = 65499;
    uint32_t _siFrameN = 65499;

    uint64_t _napTime = 0;

    QVector<double> _distances;
    QVector<qint64> _times;

public:
    ParserModem(QSharedPointer<IJournal> journal = nullptr,
                SenderParamsStation* sender = nullptr);
    ~ParserModem() {}
    /*!
     * \brief Распарсить полученные данные
     * \param params Все параметры
     * \param obj Json с данными от устройства
     */
    void parseParams(const QJsonObject& obj) override;

    void parseRK(ParamsCMS& params, const QJsonObject& obj);
    void parseORK(ParamsCMS& params, const QJsonObject& obj);
    void parseSI(ParamsCMS& params, const QJsonObject& obj);

private:
    /*!
     * \brief Записать в файл данные РКО
     * \param params Параметры
     * \param distanse Дальность
     */
    void writeParamsORM(const int64_t distanse);
};

#endif // PARSERMODEM_H
