#include "linkingFcc/infornation/ParamsController/ParamsController.h"

void ParamsController::setNewParams()
{
    auto command = params.getCurrentCommandControl();
    QString event{"КУ №%1 исполнена полностью"};
    _journal->writeEvent(event.arg(static_cast<uint16_t>(command)));

    switch (command)
    {

    case CommandsControl::COMMAND_4000 :
    {
        // а если подключено к ЦУП?
        if(params.getNumberKA() == 0)
        {
            setCorrectMode();
            params.setCurrentModeStation(static_cast<uint16_t>(CommandsControl::COMMAND_4000));
        }
        params.setNumberKA();
        params.setParamsSession();
        break;
    }

    case CommandsControl::COMMAND_4001 :
    {
        setCorrectMode(false, false, false, true);
        params.setCurrentModeStation(static_cast<uint16_t>(CommandsControl::COMMAND_4001));
        break;
    }

    case CommandsControl::COMMAND_4003 :
    {
        setCorrectMode(false, false, true);
        params.setCurrentModeStation(static_cast<uint16_t>(CommandsControl::COMMAND_4003));
        break;
    }

    case CommandsControl::COMMAND_4005 :
    {
        setCorrectMode(false, true);
        params.setCurrentModeStation(static_cast<uint16_t>(CommandsControl::COMMAND_4005));
        break;
    }

    case CommandsControl::COMMAND_4006 :
    {
        setCorrectMode(true);
        params.setCurrentModeStation(static_cast<uint16_t>(CommandsControl::COMMAND_4006));
        break;
    }

        // установка времени
    case CommandsControl::COMMAND_4018 :
    {
        break;
    }

    case CommandsControl::COMMAND_4022:
    {
        params.getInfoFC()->getRefInfoControl()->setNumberTicketedOTC(0);
        params.setIsSendingSingleCmd(false);
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS, false);
        params.getSingleCommand().setNumberCommand(0);
        params.getInfoFC()->getRefInfoControl()->setTicketOTC(TicketOTC::PROCESS_OOTC, false);
        break;
    }

    case CommandsControl::COMMAND_4019 :
    {
        break;
    }

    case CommandsControl::COMMAND_4027 :
    {
        params.getInfoFC()->getRefInfoControl()->setTicketSI(TicketSI::PROCESS_SI, false);

        break;
    }

    case CommandsControl::COMMAND_4029 :
    {
        params.getInfoFC()->getRefInfoControl()->resetModeTLM();
        auto mode = params.getParamCommandControl(Words::WORD1);
        mode == 1 ? params.getInfoFC()->getRefInfoControl()->setModeTLM(ModeTLM::TLM_1KHZ, true)
                  : params.getInfoFC()->getRefInfoControl()->setModeTLM(ModeTLM::TLM_8KHZ, true);
        break;
    }

    case CommandsControl::COMMAND_4030 :
    {
        params.getInfoFC()->getRefInfoControl()->resetModeTLM();
        break;
    }

    case CommandsControl::COMMAND_4034 :
    {
        params.getInfoFC()->getRefInfoControl()->resetBandTLM();
        if(((params.getParamCommandControl(Words::WORD1) >> static_cast<uint8_t>(ModeTLM::SLIM_STRIP)) & 1u) == 1)
            params.getInfoFC()->getRefInfoControl()->setModeTLM(ModeTLM::SLIM_STRIP, true);
        if(((params.getParamCommandControl(Words::WORD1) >> static_cast<uint8_t>(ModeTLM::AVERAGE_STRIP)) & 1u) == 1)
            params.getInfoFC()->getRefInfoControl()->setModeTLM(ModeTLM::AVERAGE_STRIP, true);
        if(((params.getParamCommandControl(Words::WORD1) >> static_cast<uint8_t>(ModeTLM::WIDE_STRIP)) & 1u) == 1)
            params.getInfoFC()->getRefInfoControl()->setModeTLM(ModeTLM::WIDE_STRIP, true);
        break;
    }

    case CommandsControl::COMMAND_4038 :
    {
        if(params.getTypeSender() == TypeSender::FCC)
            params.setControl(true);
        break;
    }

    case CommandsControl::COMMAND_4039 :
    {
        //if(params.getTypeSender() == TypeSender::FCC)
            params.setControl(false);
            //params.setControlCRT(false);
        break;
    }

    case CommandsControl::COMMAND_4040 :
    {
        break;
    }

    case CommandsControl::COMMAND_4041 :
    {
        params.getInfoFC()->setSystemState(SystemState::DOPLER_COMPLECT_TD,
                                          params.getCommands().getParam(Words::WORD1));
        break;
    }

    case CommandsControl::COMMAND_4042 :
    {
        params.getInfoFC()->setSystemState(SystemState::DOPLER_COMPLECT_ANSWER,
                                          params.getCommands().getParam(Words::WORD1));
        break;
    }

    case CommandsControl::COMMAND_4043 :
    {
        params.getInfoFC()->getRefInfoControl()->setDopplerFreqPrediction(0);
        break;
    }

    case CommandsControl::COMMAND_4048 :
    case CommandsControl::COMMAND_4045 :
    {
        auto mshy = params.getParamCommandControl(Words::WORD1) + 2;
        //params.getInfoFC().setComplects(static_cast<Complects>(mshy), true);
        break;
    }

    case CommandsControl::COMMAND_4051 :
    {
        _journal->writeEvent(QString("Включен режим ЗРР"));
        //params.getInfoFC().setSystemState(SystemState::MODE_CLOSE, true);
        break;
    }

    case CommandsControl::COMMAND_4052 :
    {
        _journal->writeEvent(QString("Выключен режим ЗРР"));
        //params.getInfoFC().setSystemState(SystemState::MODE_CLOSE, false);
        break;
    }

    case CommandsControl::COMMAND_4054 :
    {
        params.setNumberSingleCommand(static_cast<uint16_t>(SINGLE_COMMAND::SINGLE_COMMAND_6001));
        break;
    }

    case CommandsControl::COMMAND_4055 :
    {
        params.setNumberSingleCommand(static_cast<uint16_t>(SINGLE_COMMAND::SINGLE_COMMAND_6002));
        break;
    }

    case CommandsControl::COMMAND_4056 :
    {
        params.setNumberSingleCommand(static_cast<uint16_t>(SINGLE_COMMAND::SINGLE_COMMAND_6003));
        break;
    }

    case CommandsControl::COMMAND_4057 :
    {
        params.setNumberSingleCommand(static_cast<uint16_t>(SINGLE_COMMAND::SINGLE_COMMAND_6004));
        break;
    }

    case CommandsControl::COMMAND_4058 :
    {
        params.setNumberSingleCommand(static_cast<uint16_t>(SINGLE_COMMAND::SINGLE_COMMAND_6005));
        break;
    }

    case CommandsControl::COMMAND_4059 :
    {
        params.setNumberSingleCommand(static_cast<uint16_t>(SINGLE_COMMAND::SINGLE_COMMAND_6006));
        break;
    }

    default:
        break;
    }
}
