#ifndef BASECOMMANDCONTROL_H
#define BASECOMMANDCONTROL_H

#include <stdint.h>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>

#include "linkingFcc/infornation/CommandControl/StructControlCommand.h"
#include "linkingFcc/Structs/Words.h"

/// Тип отправителя
enum class TypeSender : uint8_t
{
    BLOCKER,
    CRT,
    FCC,
    UNDEFINED
};

/// Тип станции
enum class TypeCMS : uint16_t
{
    NO,
    MAIN,
    UNIQUE = 649
};

struct ParamsSession
{
    int16_t numberSeans{0};               ///< № сеанса
    int16_t numberVitok{0};               ///< № витка
};

class BaseCommandControl
{
public:
    BaseCommandControl() = default;
    virtual ~BaseCommandControl() = default;

    /*!
     * \brief Парсинг команды, которая пришла из ЦУП
     * \param nKA Номер КА
     * \param header Заголовок
     */
    virtual void unserializeCommand(uint16_t, HeaderControlCommand&) {}

    /*!
     * \brief Сформировать json для отправки в блокер
     * \return Объект json
     */
    QJsonObject vectorData();

    uint16_t numKA() const;
    void setNumKA(const uint16_t &numKA);

    CommandsControl numCommand() const;
    void setNumCommand(const CommandsControl &numCommand);

    uint16_t getParam(const Words word) const;
    void setParams(const QVector<int16_t> &value);

    uint16_t getCurrentMode() const;
    void setCurrentMode(const uint16_t &currentMode);

    TypeSender getCurrentType() const;
    void setCurrentType(const TypeSender &currentType);

    void resetCommandControl();
    /*!
     * \brief Добавить параметр в список параметров команды управления
     * \param param Параметр
     */
    void addParam(const uint16_t param);
    /*!
     * \brief Очистить список параметров
     */
    void clear();

    void setParamsSession(const int16_t session, const int16_t vitok);
    ParamsSession getParamsSession() const;

protected:
    uint16_t _numKA{0};                                       ///< номер КА
    CommandsControl _numCommand{CommandsControl::COMMAND_4000}; ///< номер команды
    QVector<int16_t> params;                                  ///< список параметров
    uint16_t _currentMode{4000};                              ///< текущий режим работы
    TypeSender _currentType{TypeSender::FCC};                 ///< Текущий тип присылавшего пакет
    ParamsSession paramsSession;
    TypeCMS type{TypeCMS::MAIN};
};

#endif // BASECOMMANDCONTROL_H
