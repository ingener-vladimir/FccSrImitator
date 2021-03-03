#include "linkingFcc/Senders/TicketsSender.h"

// DO NOT EDIT!!!!

long decimalToOctal(long n)
{
    int remainder;
    long octal = 0, i = 1;

    while(n != 0)
    {
        remainder = n % 8;
        n = n / 8;
        octal = octal + (remainder * i);
        i = i * 10;
    }
    return octal;
}

bool SenderTickets::prepareTicketByteArray(const QJsonObject &obj, ParamsCMS& params) {

    bool ret = false;
    static uint8_t _faultCounter = 0;

    QJsonValue jv;

    qDebug() << "[TICKET] new:" << obj;

    params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::SEND_MASK, false);

    jv = obj.value("isSendingSpecialSingleCmd");
    bool isORK = false;
    if(!jv.isUndefined()) {
        bool value = jv.toBool();
        isORK = value;

        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS_OOTC, value);
        params.setIsSendingSingleCmd(value);
        params.setIsSendingSpecialSingleCmd(value);
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS, value);
        qDebug() << "[TICKET] ORK" << value;
    } else
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS_OOTC, false);

    int cmdNum = 0;
    jv = obj.value("singleCmdNum");
    if(!jv.isUndefined()) {
        cmdNum = jv.toInt();

        if(cmdNum < 6000)
            cmdNum = decimalToOctal(cmdNum);
        if(isORK && cmdNum < 6000)
            cmdNum += 6000;

        params.getInfoFC()->getRefInfoControl()->setNumberTicketedOTC(cmdNum);
        params.setNumberSingleCommand(static_cast<uint16_t>(cmdNum));
        qDebug() << "[TICKET] CMD NUM"  << cmdNum;
    }

    jv = obj.value("cmd_state");
    if(!jv.isUndefined()) {
        QString mask = jv.toString();

        if(mask == "start" && obj.value("type_cmd").toString() == "single_cmd") {
            if(_journal)
                _journal->writeEvent(QString("Выдана РК: %1").arg(cmdNum));
        }

        if(mask == "start" && obj.value("type_cmd").toString() == "SSCmd") {
            if(_journal)
                _journal->writeEvent(QString("Выдана OРК: %1").arg(cmdNum));
        }

        if(mask == "start" && obj.value("type_cmd").toString() == "specialInfo") {
             params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::ON_SI, true);
        }

        if(mask == "end_phrase" && obj.value("type_cmd").toString() == "specialInfo") {
            if(_journal)
                _journal->writeEvent(QString("Выдана фраза: %1").arg(obj.value("numSiPhraseWithTicket").toInt()));
        }

        if(mask == "exec") {
            _faultCounter++;
            params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::SEND_MASK, true);
        }

        if(mask == "end" && obj.value("type_cmd").toString() == "specialInfo") {
            jv = obj.value("specialInfoState");
            if(!jv.isUndefined()) {
                int state = jv.toInt();

                if(_journal && state == 1)
                    _journal->writeEvent(QString("Вся СИ выдана"));

                if(_journal && state == 2)
                    _journal->writeEvent(QString("СИ выдана не полностью"));
            }
        }
    }

    jv = obj.value("isSendingSingleCmd");
    if(!jv.isUndefined()) {
        bool value = jv.toBool();

        params.setIsSendingSingleCmd(value);
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS, value);

        qDebug() << "[TICKET] RK" << value;
    }


    jv = obj.value("singleCmdPlusTicket");
    if(!jv.isUndefined()) {
        bool ticket = jv.toBool();
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PLUS, ticket);

        if(_journal)
            _journal->writeEvent(QString("Получена +КВ"));

        qDebug() << "[TICKET] PLUS QRK" << ticket;
    }

    jv = obj.value("singleCmdMinusTicket");
    if(!jv.isUndefined()) {
        bool ticket = jv.toBool();
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::MINUS, ticket);

        if(_journal)
            _journal->writeEvent(QString("Получена -КВ"));

        qDebug() << "[TICKET] MINUS QRK" << ticket;
    }

    jv = obj.value("singleCmdZeroTicket");
    if(!jv.isUndefined()) {
        bool ticket = jv.toBool();
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::NULL_OTC, ticket);

        if(_journal)
            _journal->writeEvent(QString("Получена 0КВ"));

        qDebug() << "[TICKET] ZERO QRK" << ticket;
    }

    int numSIPhrase = 0;
    jv = obj.value("numSiPhraseWithTicket");
    if(!jv.isUndefined()) {
        numSIPhrase = jv.toInt();
        params.getInfoFC()->getRefInfoControl()->setNumberTicketedSI(numSIPhrase);
    }

    jv = obj.value("specialInfoPlusTicket");
    if(!jv.isUndefined()) {
        bool ticket = jv.toBool();
        params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PLUS, ticket);

        if(_journal)
            _journal->writeEvent(QString("Получена +КВ"));

        jv = obj.value("reverseSiPhraseNumber");
        if(!jv.isUndefined()) {
            int revSI = jv.toInt();
            if(revSI <= 0) {
                params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PROCESS_SI, false);
                params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::STOP_SI, false);
                params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::ON_SI, false);
                ret = true;
            }
        }

        qDebug() << "[TICKET] PLUS QSI" << ticket;
    }

    jv = obj.value("specialInfoMinusTicket");
    if(!jv.isUndefined()) {
        bool ticket = jv.toBool();
        params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::MINUS, ticket);

        if(_journal)
            _journal->writeEvent(QString("Получена -КВ"));

        jv = obj.value("reverseSiPhraseNumber");
        if(!jv.isUndefined()) {
            int revSI = jv.toInt();
            if(revSI <= 0) {
                //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PROCESS_SI, false);
                //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::STOP_SI, false);
                //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::ON_SI, false);
                //ret = true;
            }
        }

        qDebug() << "[TICKET] MINUS QSI" << ticket;
    }

    jv = obj.value("specialInfoZeroTicket");
    if(!jv.isUndefined()) {
        bool ticket = jv.toBool();
        params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::NULL_SI, ticket);

        if(_journal)
            _journal->writeEvent(QString("Получена 0КВ"));

        jv = obj.value("reverseSiPhraseNumber");
        if(!jv.isUndefined()) {
            int revSI = jv.toInt();
            if(revSI <= 0) {
                //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PROCESS_SI, false);
                //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::STOP_SI, false);
                //params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::ON_SI, false);
                //ret = true;
            }
        }

        qDebug() << "[TICKET] 0 QSI" << ticket;
    }

    jv = obj.value("pauseSpecialInfo");
    if(!jv.isUndefined()) {
        bool pauseSI = jv.toBool();
        params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::STOP_SI, pauseSI);
        params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::ON_SI, !pauseSI);
    }


    jv = obj.value("cmd_state");
    if(!jv.isUndefined()) {
        QString value = jv.toString();
        if(value == "end") {
            params.setIsSendingSingleCmd(false);
            params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS, false);
            params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PROCESS_SI, false);
            params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::STOP_SI, false);
            params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::ON_SI, false);
            params.getInfoFC()->getRefInfoControl()->setNumberTicketedSI(0);
            ret = true;
            _faultCounter = 0;
        }
    }

    jv = obj.value("FaultsCounter");
    if(!jv.isUndefined()) {
        params.getInfoFC()->getRefInfoControl()->setTicketOTCFaultCounter(jv.toInt());
    }

    return ret;
}
