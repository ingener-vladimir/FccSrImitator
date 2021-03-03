#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/ProcessorFormularServer.h"
#include "utils/NetworkPackageUtils.h"

int ProcessorFormularServer::numberClient = 0;

ProcessorFormularServer::ProcessorFormularServer(QSharedPointer<GUIExchangeAdapter> guiExchangeAdapter)
    : _guiExchangeAdapter(guiExchangeAdapter)
{
    _currentNumber = ++numberClient;
}

ProcessorFormularServer::~ProcessorFormularServer()
{
    if(_guiExchangeAdapter)
        _guiExchangeAdapter->resetControl(_currentNumber);
}

void ProcessorFormularServer::setGuiExchangeAdapter(QSharedPointer<GUIExchangeAdapter> guiExchangeAdapter)
{
    _guiExchangeAdapter = guiExchangeAdapter;
}

void ProcessorFormularServer::setFactoryFormular(QSharedPointer<IFactoryFormular> factory)
{
    _factory = factory;
}

void ProcessorFormularServer::decodeByteArray(QByteArray &array)
{
    if(!_factory || !_guiExchangeAdapter)
        return;

    QByteArray unescapeArray = NetworkPackageUtils::unescapeImcomingMessage(array);
    Header header(unescapeArray);

    header.getHeader().Code = CodeTicket::TICKET_00;

    FactoryFormularFCC* factory = dynamic_cast<FactoryFormularFCC*>(_factory.data());
    ParamsCMS& params = ParamsSingleton::getInstance();
    factory->setLastHeader(header);

    if(header.getHeader().NNIP_KTC != params.getNumberNIP())
    {
        header.getHeader().Code = CodeTicket::TICKET_06;
        header.getHeader().NNIP_KTC = params.getNumberNIP();
        factory->addTicket(header);
        _guiExchangeAdapter->writeCommonLog(QString("ЦУП: Принята директива №%1. Неверный НИП").arg((uint8_t)header.getHeader().NDIR));
        return;
    }

    header.getHeader().NNIP_KTC = params.getNumberNIP();

    if(needCheck(header.getHeader().NDIR, params))
        checkValidParamsSession(header, params);

    if(header.getHeader().NDIR != Directive::DIR_19)
        _guiExchangeAdapter->writeCommonLog(QString("ЦУП: Принята директива №%1").arg((uint8_t)header.getHeader().NDIR));
    switch (header.getHeader().NDIR)
    {

    case Directive::DIR_1 :
    {
        factory->addTicket(header);
        break;
    }

    case Directive::DIR_2 :
    {
        factory->addTicket(header);
        break;
    }

    case Directive::DIR_3 :
    {
        if(header.getHeader().NFORM != TypeInfo::INFO_900)
            header.getHeader().Code = CodeTicket::TICKET_01;

        header.getHeader().NSEANS = params.getNumberSeans();
        header.getHeader().NVITKA = params.getNumberVitok();

        qDebug() << "[IP03] get L:" << array.size() << "header:" << header.lengthData();

        auto arrayTD = array.right(array.size() - sizeof(daq::Header));
        if(!_guiExchangeAdapter->writeFileTD(arrayTD))
            header.getHeader().Code = CodeTicket::TICKET_28;
        factory->addTicket(header);

        break;
    }

    case Directive::DIR_5 :
    {
        _guiExchangeAdapter->stopSendingTmi();
        factory->addTicket(header);
        break;
    }

    case Directive::DIR_12 :
    {
        PackageDirective12 packageDir12(unescapeArray);
        factory->addPackageDirective112(header, packageDir12.getData(), packageDir12.getTime());
        break;
    }

    case Directive::DIR_13 :
    {
        factory->addTicket(header);
        break;
    }

    case Directive::DIR_14 :
    {
        factory->addTicket(header);
        break;
    }

    case Directive::DIR_15 :
    {
        factory->addTicket(header);
        _guiExchangeAdapter->resetFileSI();
        break;
    }

    case Directive::DIR_16 :
    {
        if(unescapeArray.size() > (sizeof(daq::Header)))
            unserializeDataPD16(header, unescapeArray, params);
        else
            header.getHeader().Code = CodeTicket::TICKET_28;

        if(_needSendTicket)
            factory->addTicket(header);
        break;
    }

    case Directive::DIR_17 :
    {
            if(header.getHeader().NKA == 0) {
                header.getHeader().Code = CodeTicket::TICKET_02;
                factory->addTicket(header);
                break;
            }

        if(header.getHeader().NFORM == TypeInfo::INFO_1888)
            _guiExchangeAdapter->startSendingTmi(TmiFormat::OLD_TMI_FORMAT);

        else if (header.getHeader().NFORM == TypeInfo::INFO_1889)
            _guiExchangeAdapter->startSendingTmi(TmiFormat::NEW_TMI_FORMAT);

        else
            header.getHeader().Code = CodeTicket::TICKET_01;

        factory->addTicket(header);
        break;
    }

    case Directive::DIR_18 :
    {
        //qDebug() << "[HEADER 18]" << header.getHeader().NKA << header.getHeader().NSEANS << header.getHeader().NVITKA << params.getNumberKA();
        if(params.getNumberKA() == header.getHeader().NKA) {
            params.setParamsSession(header.getHeader().NKA, header.getHeader().NSEANS, header.getHeader().NVITKA);
            factory->addTicket(header);
            break;
        }

        bool isControl = _guiExchangeAdapter->checkControlFCC(_currentNumber);
        if(isControl == false)
            _guiExchangeAdapter->setFactory(_factory);

        FactoryCommandControl command(header.getHeader().NKA);
        command.getCommandControl()->setNumKA(header.getHeader().NKA);
        command.getCommandControl()->setParamsSession(header.getHeader().NSEANS, header.getHeader().NVITKA);
        _guiExchangeAdapter->createParamsCMS(header.getHeader().NKA);
        params.setNumberKA(header.getHeader().NKA);
        factory->addTicket(header);
        _guiExchangeAdapter->sendParamsCommandControl(command.getCommandControl());

        break;
    }

    case Directive::DIR_19 :
    {

        //qDebug() << "[HEADER 19]" << header.getHeader().NKA << header.getHeader().NSEANS << header.getHeader().NVITKA << params.getNumberKA();
        header.resetParamsSession();
        factory->addTicket(header);
        //qDebug() << "[HEADER 19]" << header.getHeader().NKA << header.getHeader().NSEANS << header.getHeader().NVITKA << params.getNumberKA();
        /*
            if(     params.getNumberKA() == 0 &&
                    params.getNumberSeans() == 0 &&
                    params.getNumberVitok() == 0) {

                header.resetParamsSession();
                factory->addTicket(header);
                break;
            }

        params.setDefaultParams();
        FactoryCommandControl command(header.getHeader().NKA);
        header.resetParamsSession();
        factory->addTicket(header);
        _swapController->sendParamsCommandControl(command.getCommandControl());*/
        break;
    }

    case Directive::DIR_20 :
    {
        PackageDirective20 packageDir20(unescapeArray);
        factory->addTicket(header);
        break;
    }

    case Directive::DIR_25 :
    {
        factory->addTicket(header);
        break;
    }

    case Directive::DIR_98 :
    {
        QString name = QString(unescapeArray.right(unescapeArray.size() - sizeof(daq::Header)));
        if(name.isEmpty())
        {
            header.getHeader().Code = CodeTicket::TICKET_17;
            factory->addTicket(header);
            return;
        }
        factory->addPackageDirective198(header, name);
        break;
    }

    default:
        _guiExchangeAdapter->writeCommonLog(QString("ЦУП: Неизвестная директива №%1").arg((uint8_t)header.getHeader().NDIR));
        break;
    }
}

bool ProcessorFormularServer::needCheck(Directive dir, ParamsCMS& params)
{
    return params.getNumberKA() != 0
            && params.getNumberSeans() != 0
            && params.getNumberVitok() != 0
            && dir != Directive::DIR_3
            && dir != Directive::DIR_12
            && dir != Directive::DIR_13
            && dir != Directive::DIR_18
            && dir != Directive::DIR_20
            && dir != Directive::DIR_25;
}

void ProcessorFormularServer::checkValidParamsSession(Header& message, ParamsCMS& params)
{
    if(message.getHeader().NKA != params.getNumberKA())
    {
        message.getHeader().NKA = params.getNumberKA();
        message.getHeader().Code = CodeTicket::TICKET_02;
         _guiExchangeAdapter->writeCommonLog(QString("ЦУП: Директива №%1. Неверный КА").arg((uint8_t)message.getHeader().NDIR));
    }

    if(message.getHeader().NSEANS != params.getNumberSeans())
    {
        message.getHeader().NSEANS = params.getNumberSeans();
        message.getHeader().Code = CodeTicket::TICKET_04;
         _guiExchangeAdapter->writeCommonLog(QString("ЦУП: Директива №%1. Неверный номер сеанса").arg((uint8_t)message.getHeader().NDIR));
    }

    if(message.getHeader().NVITKA != params.getNumberVitok())
    {
        message.getHeader().NVITKA = params.getNumberVitok();
        message.getHeader().Code = CodeTicket::TICKET_05;
         _guiExchangeAdapter->writeCommonLog(QString("ЦУП: Директива №%1. Неверный номер витка").arg((uint8_t)message.getHeader().NDIR));
    }
}

int octalToDecimal(int num) {
   int temp = num;
   int val = 0;
   int base = 1;
   int count = temp;
   while (count) {
      int digit = count % 10;
      count = count / 10;
      val += digit * base;
      base = base * 8;
   }
   return val;
}

void ProcessorFormularServer::unserializeDataPD16(Header& header,
                                               QByteArray& array,
                                               ParamsCMS& params)
{
    _needSendTicket = true;
    if(header.getHeader().NFORM == TypeInfo::INFO_102)
    {
        auto arraySpec = array.right(array.size() - sizeof(daq::Header));
        if(!_guiExchangeAdapter->writeFileSI(arraySpec))
            header.getHeader().Code = CodeTicket::TICKET_28;
    }

    else if(header.getHeader().NFORM == TypeInfo::INFO_1101)
    {
        if(array.size() != sizeof(daq::Header) + 8)
            header.getHeader().Code = CodeTicket::TICKET_28;
        else
        {
            PackageDirective16OneTimeCommand packageOTC(array);
            packageOTC.unserialize(params.getSingleCommand());
            if(params.getSingleCommand().numberCommand() < 6000) {
                qDebug() << "[DIR16] cmdN=" << params.getSingleCommand().numberCommand();
                params.getSingleCommand().setNumberCommand(octalToDecimal(params.getSingleCommand().numberCommand()));
            }
            _guiExchangeAdapter->createSignalCommandForSend();
        }
    }

    else if(header.getHeader().NFORM == TypeInfo::INFO_1102)
    {
        _needSendTicket = false;
        FactoryCommandControl factoryCommand(header.getHeader().NKA);
        *factoryCommand.getCommandControl() = params.getCommands();
        factoryCommand.getCommandControl()->setCurrentType(TypeSender::FCC);
        factoryCommand.getCommandControl()->clear();
        PackageDirective16CommandControl packageCC(array);
        packageCC.unserialize(factoryCommand.getCommandControl());

        bool isControl{true};
        if(factoryCommand.getCommandControl()->numCommand() == CommandsControl::COMMAND_4038 ||
                factoryCommand.getCommandControl()->numCommand() == CommandsControl::COMMAND_4039)
        {
            isControl = _guiExchangeAdapter->workControl(_currentNumber, factoryCommand.getCommandControl());
            if(isControl == false)
                _guiExchangeAdapter->setFactory(_factory);
        }

        if(_guiExchangeAdapter->haveControl(_currentNumber))
            _guiExchangeAdapter->sendParamsCommandControl(factoryCommand.getCommandControl());
        else
        {
            if(isControl)
            {
                _needSendTicket = true;
                header.getHeader().Code = CodeTicket::TICKET_33;
            }
        }
    }
}
