#include "linkingFcc/GUIExchangeAdapter.h"

#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <QFile>

GUIExchangeAdapter::GUIExchangeAdapter()
{
    _journal = QSharedPointer<JournalCommon>(new JournalCommon());
    _parser = QSharedPointer<ParserEvents>(new ParserEvents(_journal));
    _parser->setSender(&_senderParams);
    _paramsController = QSharedPointer<ParamsController>(new ParamsController());
    _paramsController->setJournal(_journal);

    /*QString str = "351_10_10.ug";

    FileWorkerORM file(TypeFileORM::ANGLES);
    file.setNameFile(str);
    file.write(QByteArray(str.toLocal8Bit()));

    FileWorkerORM file1(TypeFileORM::ANGLES);
    file1.setNameFile(str);
    file1.write(QByteArray((str + "10").toLocal8Bit()));*/
}

GUIExchangeAdapter::~GUIExchangeAdapter()
{
    _journal.reset();
    _journal = nullptr;
    _parser.reset();
    _parser = nullptr;
    _paramsController.reset();
    _paramsController = nullptr;
}

void GUIExchangeAdapter::sendParamsCommandControl(QSharedPointer<BaseCommandControl> command)
{
    if(_isSend)
    {
        _queueCommandsControl.append(command);
        return;
    }

    params.setCommands(command);
    /// если тип не ЦУП и нет управления
    if(params.getTypeSender() != TypeSender::FCC && !checkControlCRT())
        return;

    auto object = params.getJsonCommandControl();

    /// если номер команды равен 4025(СИ), добавить в json фразу СИ
    if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4025)
    {
        if(!params.getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::PROCESS_SI))
            return;
        object.insert("params", QJsonArray().fromStringList({params.getConvertPhraseSpecialInformation()}));
    }

    /// если номер команды равен 4020(Установить антенну), сформировать и добавить в params строку
    if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4020)
        createCommandSetAntenna(object);

    /// если номер команды равен 4031(РКО), сформировать и добавить в params строку
    if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4031)
        createCommandModeRCO(object);

    if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4026)
        if(!params.getInfoFC()->getRefInfoControl()->getTicketSI(TicketSI::PROCESS_SI))
            return;

    /// если номер команды равен 4021(Выдать РК)
    if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4021)
        object.insert("params", QJsonArray().fromVariantList({params.getInfoFC()->getRefInfoControl()->getNumberTicketedOTC()}));

    if(!object.isEmpty() && !_isSend)
    {
        _isSend = true;
        auto command = params.getCurrentCommandControl();
        writeCommonLog(QString("%1: КУ №%2").arg(HASH_SENDER.value(static_cast<uint8_t>(params.getTypeSender()))).arg(static_cast<uint16_t>(command)));
        emit sendJsonToBlocker(object);
    }
}

void GUIExchangeAdapter::analizeAnswerFromForm(bool state)
{
    qDebug() << "SenderParamsStation::analizeAnswerFromForm" << state;

    _isSend = false;

    if(!state)
    {
        _senderParams.setCode(CodeTicket::TICKET_50);
        writeCommonLog(QString("КУ №%1 / Результат выполнения: исполнена с ошибками").arg(static_cast<uint16_t>(params.getCurrentCommandControl())));
    }
    else
    {
        if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4000)
            createParamsCMS(params.getCommands().numKA());

        setNewParams();
        _senderParams.setCode(CodeTicket::TICKET_00);

        if(params.getTypeSender() != TypeSender::FCC)
        {
            /// отдать управление станцией ЦРТ
            if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4038)
            {
                params.setControlCRT(true);
                resetControl(_currentNumber);
            }

            if(params.getControlCRT())
            {
                /// если ЦРТ прислала КУ на Отдачу управления, сбрасываем
                if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4039)
                {
                    params.setControlCRT(false);
                    resetControl(_currentNumber);
                }
            }
        }
        else
        {
            if(params.getCurrentCommandControl() == CommandsControl::COMMAND_4039)
                emit signalSendActive(_currentNumber, false);
        }
    }

    /// если тип ЦУП
    if(params.getTypeSender() == TypeSender::FCC)
        _senderParams.createTicket(params.getNumberKA());

    if(state && params.getCurrentCommandControl() == CommandsControl::COMMAND_4000)
    {
        if(params.getNumberKA() > 0)
        {
            FactoryCommandControl factory(params.getNumberNIP());
            *factory.getCommandControl() = params.getCommands();
            factory.getCommandControl()->clear();
            factory.getCommandControl()->setNumCommand(CommandsControl::COMMAND_4005);
            sendParamsCommandControl(factory.getCommandControl());

            //autoload CU for KA
            auto path = ControllerTargetDesignation().findLastTargetDesignation(params.getNumberKA());

            QString res = ControllerTargetDesignation().validateTargetDestination(path, params.getNumberKA());
            if(!res.isEmpty()) {
                writeCommonLog(res);
            } else {
                prepareSpecialCommand(path, CommandsControl::COMMAND_4910);
                prepareSpecialCommand(path, CommandsControl::COMMAND_4920);
            }
        }
        _senderParams.setLastKA(params.getNumberKA());
    }

    if(params.getNumberKA() == 0 && state)
    {
        params.setDefaultParams();
        setNewParams();
    }

    if(!_queueSpecialCC.isEmpty())
        sendSpecialCCtoBlocker(_queueSpecialCC.dequeue());
    else if(!_queueCommandsControl.isEmpty())
        sendParamsCommandControl(_queueCommandsControl.dequeue());
}

void GUIExchangeAdapter::analizeAnswerSpecialCC(bool state)
{
    Q_UNUSED(state);

    _isSend = false;

    if(!_queueSpecialCC.isEmpty())
        sendSpecialCCtoBlocker(_queueSpecialCC.dequeue());
}

void GUIExchangeAdapter::slotParamFromForm(const QJsonObject json)
{
    qDebug() << "SenderParamsStation::slotParamFromForm" << json;

    FactoryCommandControl factory(params.getNumberNIP());
    *factory.getCommandControl() = params.getCommands();
    factory.getCommandControl()->clear();
    // тип отправителя КУ
    QJsonValue jv = json.value("typeSender");
    if(!jv.isUndefined())
        factory.getCommandControl()->setCurrentType(static_cast<TypeSender>(jv.toInt()));

    // номер КА
    jv = json.value("KA");
    if(!jv.isUndefined())
    {
        if(json.value("cmd_number").toInt() == 4000 &&
                jv.toInt() == params.getNumberKA() &&
                params.getNumberKA() > 0)
            return;
    }

    factory.getCommandControl()->setNumKA(jv.toInt());

    // номер команды
    jv = json.value("cmd_number");
    if(!jv.isUndefined())
        factory.getCommandControl()->setNumCommand(static_cast<CommandsControl>(jv.toInt()));

    // слова
    jv = json.value("params");
    if(!jv.isUndefined())
    {
        auto array = jv.toArray();
        for(auto ar : array)
        {
            if(factory.getCommandControl()->numCommand() == CommandsControl::COMMAND_4031)
            {
                _dataRCO = ar.toString();
                break;
            }
            if(factory.getCommandControl()->numCommand() == CommandsControl::COMMAND_4020)
            {
                _dataAntenna = ar.toString();
                break;
            }
            factory.getCommandControl()->addParam(ar.toInt());
        }
    }

    sendParamsCommandControl(factory.getCommandControl());
}

void GUIExchangeAdapter::setNewParams()
{
    _paramsController->setNewParams();
    sendJsonCrt();
}

void GUIExchangeAdapter::onFormCompleted()
{
    sendJsonCrt();
}

void GUIExchangeAdapter::onExecBlocker(bool state)
{
    analizeAnswerFromForm(state);
}

void GUIExchangeAdapter::slotStartSendFunctionControl(const QString& host)
{
    params.setIsConnectedFCC(true);
    _journal->writeEvent(QString("Установлено соединение с ЦУП, IP-адрес %1").arg(host));
    sendJsonCrt();
}

void GUIExchangeAdapter::slotStopSendFunctionControl(const QString& id)
{
    _journal->writeEvent(QString("Соединение с ЦУП(IP - адрес %1) разорвано").arg(id));
    sendJsonCrt();
}

void GUIExchangeAdapter::openFileSI(const QString filePath)
{
    if(filePath.isEmpty())
        return;

    QUrl url(filePath);
    auto name = url.toLocalFile();
    QFile file;
    QByteArray array;
    file.setFileName(name);
    if(file.open(QIODevice::ReadOnly))
    {
        array = file.readAll();
        file.close();
    }

    FileWorkerSI fileSI;
    fileSI.write(array);

    if(createPhraseSI(array))
        writeCommonLog(QString("Загрузка файла СИ %1 завершена успешно").arg(QFileInfo(filePath).fileName()));
}

void GUIExchangeAdapter::resetFileSI()
{
    params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PROCESS_SI, false);
}

bool GUIExchangeAdapter::writeFileSI(QByteArray &array)
{
    FileWorkerSI file;
    if(!file.write(array))
        qDebug() << "SenderParamsStation::writeFileSI -> error write file SI";

    auto isSi = createPhraseSI(array);
    if(isSi)
    {
        _journal->writeEvent(QString("Получена СИ"));
        emit signalSendLogCommon();
    }
    return isSi;
}

bool GUIExchangeAdapter::writeFileTD(QByteArray &array)
{
    writeCommonLog(QString("ЦУП: Получены параметры ЦУ"));
    FileWorkerTD file;
    if(!file.write(array))
    {
        qDebug() << "SenderParamsStation::writeFileTD -> error write file TD";
        writeCommonLog(QString("Ошибка записи файла ЦУ"));
        return false;
    }

    createForSendTD(file.path());
    return true;
}

void GUIExchangeAdapter::openFileTD(const QString &nameTD)
{
    writeCommonLog(QString("КИС: Получены параметры ЦУ"));
    if(nameTD.isEmpty())
    {
        writeCommonLog(QString("Ошибка записи файла ЦУ - пустой путь к файлу"));
        return;
    }

    QUrl url(nameTD);
    auto name = url.toLocalFile();
    QFile receivedFile;
    QByteArray arrayRead;
    receivedFile.setFileName(name);
    if(receivedFile.open(QIODevice::ReadOnly))
    {
        arrayRead = receivedFile.readAll();
        receivedFile.close();
    }

    FileWorkerTD file;
    file.write(arrayRead);

    createForSendTD(file.path());
}

void GUIExchangeAdapter::createForSendTD(const QString& array)
{
    writeCommonLog(QString("Запись файла с параметрами ЦУ прошла успешно"));

    //TODO: validate for time && ka number

    QString res = ControllerTargetDesignation().validateTargetDestination(array, params.getNumberKA());
    if(!res.isEmpty()) {
        writeCommonLog(res);
        return;
    }

    prepareSpecialCommand(array, CommandsControl::COMMAND_4910);
    prepareSpecialCommand(array, CommandsControl::COMMAND_4920);
}

void GUIExchangeAdapter::prepareSpecialCommand(const QString& array,
                                           const CommandsControl command)
{
    SpecialCC special;
    special.setNumCommand(command);
    special.addParam(array);
    sendSpecialCCtoBlocker(special);
}

void GUIExchangeAdapter::sendSpecialCCtoBlocker(const SpecialCC& specialCC)
{
    if(_isSend)
    {
        _queueSpecialCC.enqueue(specialCC);
        return;
    }

    params.setSpecialCC(specialCC);
    auto object = params.getJsonSpecialCC();

    if(!object.isEmpty())
    {
        _isSend = true;
        emit sendSpecCC(object);
    }
}

void GUIExchangeAdapter::complectsDevices(const QJsonArray array)
{
    if(array.isEmpty())
        return;

    for(auto it : array)
    {
        QString uuidStr{""};
        QJsonObject obj = it.toObject();
        QJsonValue jv = obj.value("devUuid");
        if(!jv.isUndefined())
            uuidStr = jv.toString();

        int8_t kit{0};
        jv = obj.value("kitNum");
        if(!jv.isUndefined())
            kit = jv.toInt();

        jv = obj.value("kitType");
        if(!jv.isUndefined())
        {
            auto type = jv.toInt();
            setCurrentComplect(static_cast<TypeKit>(type), kit);
            if(!uuidStr.isEmpty() && _parser)
                _parser->createParser(static_cast<TypeKit>(type), uuidStr, kit);
        }
    }
}

void GUIExchangeAdapter::sendCurrentTmi(const QJsonObject &object)
{
    _senderParams.sendTMI(object, params.getNumberKA(), params.getNumberSeans(), params.getNumberVitok());
}

void GUIExchangeAdapter::onLoadScheme()
{
    //params.resetParams();

    //auto path = ControllerTargetDesignation().findLastTargetDesignation();
    //prepareSpecialCommand(path, CommandControl::COMMAND_4910);
    //prepareSpecialCommand(path, CommandControl::COMMAND_4920);

}

void GUIExchangeAdapter::sendCurrentTicket(const QJsonObject &object)
{
    bool isEnd = SenderTickets(_journal).prepareTicketByteArray(object, params);

    sendJsonCrt();
    emit signalSendIFCT();

    params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::MINUS, false);
    params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::NULL_OTC, false);
    params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PLUS, false);
    params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::MINUS, false);
    params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PLUS, false);
    params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::NULL_SI, false);

    if(isEnd)
    {
        //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PROCESS_SI, false);
        //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::STOP_SI, false);
        //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::ON_SI, false);
        params.getInfoFC()->getRefInfoControl()->setNumberTicketedOTC(0);
        params.setNumberSingleCommand(0);
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS_OOTC, false);
        params.setIsSendingSingleCmd(false);
        params.setIsSendingSpecialSingleCmd(false);
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS, false);
        params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::ON_SI, false);
        params.getInfoFC()->getRefInfoControl()->setNumberTicketedSI(0);
        params.getInfoFC()->getRefInfoControl()->setIdSI(0);
    }
}

void GUIExchangeAdapter::stopSendingTmi()
{
    _senderParams.stopSendingTmi();
}

void GUIExchangeAdapter::startSendingTmi(TmiFormat format)
{
    _senderParams.startSendingTmi(format);
}

void GUIExchangeAdapter::setFactory(QSharedPointer<IFactoryFormular> factory)
{
    _senderParams.setFactory(factory);
}

void GUIExchangeAdapter::setCurrentComplect(const TypeKit type, const int8_t numberComplect)
{
    if(TYPE_COMPLECT_MAP.contains(type) && numberComplect >= 0)
    {
        Complects comp = TYPE_COMPLECT_MAP.value(type);
        auto cplt = params.getInfoFC()->getComplects(comp);
        bool isChange{false};
        if(comp == Complects::MODEM)
        {
            /// если комплект 3(Cortex)
            if(numberComplect == NUMBER_COMPLECT_CORTEX)
            {
                params.setIsModemCortex(true);
                cplt = NUMBER_COMPLECT_CORTEX;
            }
            else
                params.setIsModemCortex(false);
        }

        if(numberComplect == 1 || numberComplect == 2)
        {
            params.getInfoFC()->setComplects(comp, (numberComplect == 1 ? false : true));
            isChange = true;
        }

        if(cplt > 0 && cplt != numberComplect)
            _journal->writeEvent(QString("Номер комплекта устройства \"%1\" изменен на %2").arg(HASH_COMPLECTS.value(static_cast<uint8_t>(comp))).arg(numberComplect));

        params.changeStateComplect(comp, isChange);
        sendJsonCrt();
    }
}

int GUIExchangeAdapter::getCurrentKa() const
{
    return static_cast<int>(params.getNumberKA());
}

int GUIExchangeAdapter::getCurrentMode() const
{
    return static_cast<int>(params.getCommands().getCurrentMode());
}

bool GUIExchangeAdapter::createPhraseSI(QByteArray &array)
{
    if(array.isEmpty())
        return false;

    if(!params.unserializeSpecialInformation(array))
        return false;

    params.getInfoFC()->getRefInfoControl()->setIdSI(params.getSpecialInfo().idSI());
    params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PROCESS_SI, true);
    sendJsonCrt();
    return true;
}

void GUIExchangeAdapter::parseListEvent(const QString &uuid, const QJsonDocument &event)
{
    if(_parser)
    {
        _parser->parseEvents(uuid, event);
        sendJsonCrt();
    }
}

void GUIExchangeAdapter::sendJsonCrt()
{
    auto array = params.serializeToJSON();
    emit sendJsonToCrt(array);
    emit signalSendLogCommon();
}

void GUIExchangeAdapter::createCommandSetAntenna(QJsonObject& object)
{
    QString strJson{""};
    if(params.getTypeSender() == TypeSender::FCC)
    {
        int mode = params.getParamCommandControl(Words::WORD1);

        QJsonObject obj;
        obj.insert("mode", QJsonValue(mode));

        int azimuth = (uint16_t)params.getParamCommandControl(Words::WORD3) << 16;
        azimuth |=  (uint16_t)params.getParamCommandControl(Words::WORD2);

        if(mode >= 8) {
            azimuth = params.getParamCommandControl(Words::WORD3) << 16;
            azimuth |=  params.getParamCommandControl(Words::WORD2);
        }

        daq::Degree az;
        az.fromWORD(azimuth, 10);
        obj.insert("azim", QJsonValue(az.toDouble()));
        daq::Degree el;
        el.fromWORD(params.getParamCommandControl(Words::WORD4), 10);
        obj.insert("elev", QJsonValue(el.toDouble()));
        obj.insert("amenAZ", QJsonValue(params.getInfoFC()->getRefInfoControl()->getCorrectionAzimuth()));
        obj.insert("amenUM", QJsonValue(params.getInfoFC()->getRefInfoControl()->getCorrectionElevation()));

        QJsonDocument doc(obj);
        QByteArray docByteArray = doc.toJson(QJsonDocument::Compact);
        strJson = QLatin1String(docByteArray);
    }
    else
        strJson = _dataAntenna;


    if(object.contains("params"))
        object.remove("params");

    object.insert("params", QJsonArray().fromStringList({strJson}));
}

void GUIExchangeAdapter::createCommandModeRCO(QJsonObject& object)
{
    QString strJson{""};
    uint8_t mode{0};
    uint8_t temp{1};
    uint16_t count{0};
    if(params.getTypeSender() == TypeSender::FCC)
    {
        parseModeRCObyFCC(mode, temp, count);
        QJsonObject obj;
        obj.insert("mode", QJsonValue(mode));
        obj.insert("interval", QJsonValue(temp));
        obj.insert("count", QJsonValue(count));

        QJsonDocument doc(obj);
        strJson = doc.toJson(QJsonDocument::Compact);
    }
    else
        strJson = _dataRCO;

    if(object.contains("params"))
        object.remove("params");

    object.insert("params", QJsonArray().fromStringList({strJson}));
}

void GUIExchangeAdapter::parseModeRCObyFCC(uint8_t &mode, uint8_t &temp, uint16_t &count)
{
    /// режим
    if(((params.getParamCommandControl(Words::WORD1) >> static_cast<uint8_t>(ModeORM::CHANGE_ANGLE)) & 1u) == 1)
        mode = 2;

    /// темп измерений
    if(((params.getParamCommandControl(Words::WORD1) >> 4) & 1u) == 1)
        temp = 1;
    else if(((params.getParamCommandControl(Words::WORD1) >> 5) & 1u) == 1)
        temp = 2;

    /// количество измерений углов
    count = params.getParamCommandControl(Words::WORD2);
}

bool GUIExchangeAdapter::checkControlCRT()
{
    bool res{true};

    if(params.getCurrentCommandControl() != CommandsControl::COMMAND_4038
            && params.getCurrentCommandControl() != CommandsControl::COMMAND_4039
            && !params.getControlCRT())
    {
        writeCommonLog(QString("Другой комплект КИС управляет станцией"));
        res = false;
    }

    return res;
}

void GUIExchangeAdapter::writeCommonLog(const QString &log)
{
    _journal->writeEvent(log);
    emit signalSendLogCommon();
}

QJsonArray GUIExchangeAdapter::getCommonJournal()
{
    return _journal->getLogs();
}

bool GUIExchangeAdapter::haveControl(const uint16_t number)
{
    bool res{false};
    if((_currentNumber == number) && !params.getControlCRT())
        res = params.getControl();

    return res;
}

bool GUIExchangeAdapter::workControl(const uint16_t number, QSharedPointer<BaseCommandControl> command)
{  
    bool res{params.getControl() || params.getControlCRT()};
    if(!res)
    {
        setControllerStation(number);
        sendParamsCommandControl(command);
    }

    return res;
}

bool GUIExchangeAdapter::checkControlFCC(const uint16_t number)
{
    bool res{params.getControlCRT()};
    if(!res)
    {
        params.setControl(true);
        setControllerStation(number);
    }

    return res;
}

void GUIExchangeAdapter::setControllerStation(const uint16_t number)
{
    _currentNumber = number;
    _queueCommandsControl.clear();
    _queueSpecialCC.clear();
    emit signalSendActive(_currentNumber, true);
}

void GUIExchangeAdapter::resetControl(const uint16_t number)
{
    if(_currentNumber == number)
    {
        params.setControl(false);
        //_senderParams.setFactory(nullptr);
        _queueCommandsControl.clear();
        _queueSpecialCC.clear();
        emit signalSendActive(_currentNumber, false);
    }
}

void GUIExchangeAdapter::writeSingleCommand(const QJsonObject object)
{
    params.getSingleCommand().unserializeCommand(object);
    sendSignalCommand(object);
}

void GUIExchangeAdapter::createSignalCommandForSend()
{
    QJsonObject obj;
    obj.insert("cmd_num", QJsonValue(params.getSingleCommand().numberCommand()));
    obj.insert("nrk", QJsonValue(params.getSingleCommand().numberCommand()));
    /// 1 - одноразовая команда, 0 - циклическая команда,
    obj.insert("cmd_type", QJsonValue(params.getSingleCommand().typeCommand()));
    /// 1 - относительное время выдачи, 0 - фиксированное время выдачи,
    obj.insert("cmd_type_delivery", QJsonValue(params.getSingleCommand().typeTimeDelivery()));
    obj.insert("cmd_dt", QJsonValue(params.getSingleCommand().getDateTime()));

    sendSignalCommand(obj);
}

void GUIExchangeAdapter::sendSignalCommand(const QJsonObject& object)
{
    //params.getInfoFC()->setNumberTicketedOTC(params.getSingleCommand().numberCommand());

    QJsonDocument doc(object);
    QByteArray docByteArray = doc.toJson(QJsonDocument::Compact);
    QString strJson = QLatin1String(docByteArray);

    prepareSpecialCommand(strJson, CommandsControl::COMMAND_4930);
    sendJsonCrt();
}

void GUIExchangeAdapter::disconnectAll()
{
    emit signalCloseAll();
}

void GUIExchangeAdapter::sendMapConnection(const QJsonObject& object)
{
    if(object.value("clients").toArray().isEmpty())
    {
        params.setIsConnectedFCC(false);
        sendJsonCrt();
    }
    emit signalSendMapConnection(object);
}

void GUIExchangeAdapter::setCurrentNumber(const uint16_t &currentNumber)
{
    _currentNumber = currentNumber;
}

void GUIExchangeAdapter::createParamsCMS(const uint16_t ka)
{
    if(params.getNumberKA() != ka)
    {
        _factoryParams.createParamsCMS(ka, params.getFunctionControl());
        
        if(_factoryParams.paramsController())
        {
            _paramsController.reset();
            _paramsController = nullptr;
            _paramsController = _factoryParams.paramsController();
            _paramsController->setJournal(_journal);
        }
    }
}


