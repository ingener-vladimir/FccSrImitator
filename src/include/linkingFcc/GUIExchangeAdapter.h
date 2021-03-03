#ifndef SWAPCONTROLLER_H
#define SWAPCONTROLLER_H

/*!
    \file
    \brief Класс отправки команд управления в блокер и отправки параметров в ЦУП
    \author Саньков Владимир
    \version 0.1
    \date октябрь 2019 г.
*/

#include <QObject>
#include <QString>
#include <QRegExp>
#include <QQueue>
#include <QJsonDocument>

#include "linkingFcc/Parser/ParserEvents.h"
#include "linkingFcc/FileWorker/FileWorkerSI.h"
#include "linkingFcc/FileWorker/FileWorkerTD.h"
#include "linkingFcc/FileWorker/FileWorkerTmi.h"
#include "linkingFcc/Journals/JournalCommon.h"
#include "linkingFcc/FileWorker/Controllers/ControllerTargetDesignation.h"
#include "linkingFcc/infornation/CommandControl/FactoryCommandControl.h"
#include "linkingFcc/infornation/Params/FactoryParams.h"

static QHash<uint8_t, QString> HASH_SENDER
{
    {static_cast<uint8_t>(TypeSender::BLOCKER), QString("КИС ТО")},
    {static_cast<uint8_t>(TypeSender::CRT), QString("КИС")},
    {static_cast<uint8_t>(TypeSender::FCC), QString("ЦУП")}
};

static QMap<TypeKit, Complects> TYPE_COMPLECT_MAP
{
    {TypeKit::MODEM, Complects::MODEM},
    {TypeKit::CONVERTER_UP, Complects::CONVERTER_UP},
    {TypeKit::AMPLIFIER, Complects::AMPLIFIER},
    {TypeKit::MSHY, Complects::MSHY},
    {TypeKit::ANTENNA, Complects::TRAMSMITTER_ANTENNA},
    {TypeKit::NP, Complects::NP},
    {TypeKit::YAY374, Complects::YAY374},
    {TypeKit::POLAR_UP, Complects::POLAR_UP},
    {TypeKit::POLAR_DOWN, Complects::POLAR_DOWN}
};

class GUIExchangeAdapter : public QObject
{
    Q_OBJECT

    FactoryParamsCMS _factoryParams;
    ParamsCMS& params = ParamsSingleton::getInstance();
    bool _isSend{false};                 ///< Флаг состояния отправки команды управления в блокер
    QByteArray _currentDataFC;           ///< Текущий массив данных ИФКТ

    QSharedPointer<ParserEvents> _parser;///< Парсер мапы с параметрами устройства
    QSharedPointer<IJournal> _journal{nullptr};///< Журнал
    SenderParamsStation _senderParams;   ///< Отправитель параметров КИС
    uint16_t _currentNumber{0};          ///< Текущий номер подключенного клиента
    QSharedPointer<IParamsController> _paramsController;

    const QString pathFileSI{"../../../"};
    QString _dataRCO{""};                ///< Данные РКО
    QString _dataAntenna{""};            ///< Данные для установки антенны
    static const uint8_t NUMBER_COMPLECT_CORTEX = 3;
    QQueue<QSharedPointer<BaseCommandControl>> _queueCommandsControl;
    QQueue<SpecialCC> _queueSpecialCC;
    /*!
     * \brief Установка новых параметров станции при успешном выполнении команды управления
     */
    void setNewParams();
    /*!
     * \brief Отправить json на форму ЦРТ
     * \param array Массив данных
     */
    void sendJsonCrt();
    /*!
     * \brief Создать фразу СИ
     * \param array Массив слов
     */
    bool createPhraseSI(QByteArray& array);
    /*!
     * \brief Установить текущие комплекты
     * \param Идентификатор комплекта
     * \param Номер комплекта
     */
    void setCurrentComplect(const TypeKit type, const int8_t numberComplect);
    /*!
     * \brief Получить
     * \param array Массив данных
     * \return Результат выполнения
     */
    QByteArray getDataTD();
    /*!
     * \brief Отправить Json специльной команды
     */
    void sendSpecialCCtoBlocker(const SpecialCC &specialCC);
    /*!
     * \brief Создать пользовательскую КУ с ЦУ и отправить в блокер
     * \param array Массив данных
     */
    void createForSendTD(const QString &array);
    /*!
     * \brief Создание команды для управления антенной
     * \param object json объект с параметрами
     */
    void createCommandSetAntenna(QJsonObject &object);
    /*!
     * \brief Создание команды для установки режима РКО
     * \param object json объект с параметрами
     */
    void createCommandModeRCO(QJsonObject &object);
    /*!
     * \brief Распарсить данные по РКО от ЦУПа
     * \param mode Режим
     * \param temp Темп измерений
     * \param count Количество измерений
     */
    void parseModeRCObyFCC(uint8_t &mode, uint8_t &temp, uint16_t &count);
    /*!
     * \brief Проверить на наличие управления от ЦРТ
     * \return Результат проверки
     */
    bool checkControlCRT();
    /*!
     * \brief Подготовить специальную команду в необходимый формат
     * \param array Данные
     * \param command Команда
     */
    void prepareSpecialCommand(const QString &array, const CommandsControl command);
    /*!
     * \brief Отправить разовую команду
     * \param object Данные РК
     */
    void sendSignalCommand(const QJsonObject &object);
    /*!
     * \brief Установить управляющий ЦУП
     * \param number Номер
     */
    void setControllerStation(const uint16_t number);
public:
    GUIExchangeAdapter();
    ~GUIExchangeAdapter();
    /*!
     * \brief Отправить параметры команды управления в блокер
     */
    void sendParamsCommandControl(QSharedPointer<BaseCommandControl> command);
    /*!
     * \brief Проанализировать ответ от блокера по выполнению команды
     * \param state Результат выполнения
     */
    void analizeAnswerFromForm(bool state);
    /*!
     * \brief Записать файл СИ
     * \param array Массив данных
     */
    bool writeFileSI(QByteArray& array);
    /*!
     * \brief Записать файл ЦУ
     * \param array Массив данных
     */
    bool writeFileTD(QByteArray& array);
    /*!
     * \brief Записать событие в журнал
     * \param log Событие
     */
    void writeCommonLog(const QString& log);
    /*!
     * \brief Остановить выдачу ТМИ
     */
    void stopSendingTmi();
    /*!
     * \brief Начать выдачу ТМИ
     * \param format Формат ТМИ
     */
    void startSendingTmi(TmiFormat format);
    /*!
     * \brief Установить текущий номер клиента
     * \param currentNumber Номер
     */
    void setCurrentNumber(const uint16_t &currentNumber);
    /*!
     * \brief Есть ли клиент, который уже управляет
     * \param number Номер клиента
     * \return
     */
    bool haveControl(const uint16_t number);
    /*!
     * \brief Установить управление
     * \param number Номер клиента
     * \return
     */
    bool workControl(const uint16_t number, QSharedPointer<BaseCommandControl> command);
    /*!
     * \brief Сбросить управление
     * \param number Номер клиента
     */
    void resetControl(const uint16_t number);
    /*!
     * \brief Создать пользовательскую команду и отправить в блокер
     */
    void createSignalCommandForSend();
    /*!
     * \brief Проверка на существование управляющего ЦУП
     * \param number Номер
     * \return Результат проверки
     */
    bool checkControlFCC(const uint16_t number);

    void createParamsCMS(const uint16_t ka);
public slots:
    /*!
     * \brief Получить журнал общих событий
     * \return Массив Json
     */
    QJsonArray getCommonJournal();
    /*!
     * \brief Получить json с командой от формы ЦРТ
     * \param json Объект с командой
     */
    void slotParamFromForm(const QJsonObject json);
    /*!
     * \brief Вызов после загрузки схемы ЦРТ
     */
    void onFormCompleted();
    void onExecBlocker(bool state);
    /*!
     * \brief Начать отправку ИФКТ в ЦУП
     */
    void slotStartSendFunctionControl(const QString& host);
    /*!
     * \brief Прекратить отправку ИФКТ в ЦУП
     */
    void slotStopSendFunctionControl(const QString& id);
    /*!
     * \brief Открыть и прочитать файл с СИ
     * \param fileName Путь к файлу
     */
    void openFileSI(const QString filePath);
    /*!
     * \brief Сбросить запись СИ
     */
    void resetFileSI();
    /*!
     * \brief Парсинг событий от устройств
     * \param Список событий
     */
    void parseListEvent(const QString &uuid, const QJsonDocument &event);

    int getCurrentKa() const;
    int getCurrentMode() const;
    /*!
     * \brief Запись разовой команды
     * \param object json с параметрами РК
     */
    void writeSingleCommand(const QJsonObject object);
    /*!
     * \brief Открыть файл с ЦУ
     * \param nameTD Имя файла
     */
    void openFileTD(const QString& nameTD);
    /*!
     * \brief Принять мапу комплектов
     * \param object Json-object
     */
    void complectsDevices(const QJsonArray array);
    /*!
     * \brief Отправить текущий кадр ТМИ
     */
    void sendCurrentTmi(const QJsonObject& object);
    /*!
     * \brief Выполнить действия при загрузке схемы
     */
    void onLoadScheme();
     /*!
      * \brief Проанализировать ответ от блокера по выполнению пользовательской команды
      */
    void analizeAnswerSpecialCC(bool state);
    /*!
     * \brief Отключить все ЦУП
     */
    void disconnectAll();

    void sendMapConnection(const QJsonObject& object);

    void sendCurrentTicket(const QJsonObject& object);

    void setFactory(QSharedPointer<IFactoryFormular> factory);

signals:
    /*!
     * \brief Отправить json на форму ЦРТ
     * \param jsonData Данные для отправки
     */
    void sendJsonToCrt(QJsonObject jsonData);
    /*!
     * \brief Отправить json в блокер
     * \param jsonData Данные для отправки
     */
    void sendJsonToBlocker(QJsonObject jsonData);
    /*!
     * \brief Сигнал для отправки общего журнала
     */
    void signalSendLogCommon();
    /*!
     * \brief Отправить специальную КУ в блокер
     * \param jsonData Данные для отправки
     */
    void sendSpecCC(QJsonObject jsonData);
    /*!
     * \brief Сигнал отправки внеочередного ИФКТ
     */
    void signalSendIFCT();
    /*!
     * \brief Закрыть соединени со всеми клиентами
     */
    void signalCloseAll();
    /*!
     * \brief Отправить номер ЦУП, который управляет станцией
     */
    void signalSendActive(const int number, const bool state);
    /*!
     * \brief Отправить в ЦРТ список подключенных ЦУП
     * \param object
     */
    void signalSendMapConnection(const QJsonObject& object);
};

#endif // SWAPCONTROLLER_H
