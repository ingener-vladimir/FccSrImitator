#include "linkingFcc/infornation/Params/FactoryParams.h"
#include "linkingFcc/FileWorker/BaseFileWorker.h"

FactoryParamsCMS::FactoryParamsCMS()
{
    struct OptionsKISFileWorker: public BaseFileWorker
    {
        OptionsKISFileWorker()
        {
            file.setFileName(filePath + "/settings.json");
        }
        virtual ~OptionsKISFileWorker() {}

        bool write(const QByteArray&) override { return true; }
        QByteArray read() override
        {
            if(file.open(QIODevice::ReadOnly))
            {
                return file.readAll();
            }

            return QByteArray();
        }
    } opt;

    QByteArray array = opt.read();
    if(array.size() > 0)
    {
        QJsonDocument jsonDoc = QJsonDocument::fromBinaryData(array);
        if(jsonDoc.isNull() || jsonDoc.isEmpty())
            jsonDoc = QJsonDocument::fromJson(array);

        if(jsonDoc.isNull() || jsonDoc.isEmpty())
        {
            qDebug()<<"[SchemeController] Empty kits file";
            return;
        }

        QJsonObject root = jsonDoc.object();

        if(!root.value("nip").isUndefined())
            params.setNumberNIP(root.value("nip").toInt());
    }
}

QSharedPointer<BaseParamsController> FactoryParamsCMS::paramsController() const
{
    return _paramsController;
}

void FactoryParamsCMS::createParamsCMS(const uint16_t ka, StructFunctionControl* control)
{
    switch(ka)
    {

    case 649:
    {
        _functionControl = QSharedPointer<FunctionControl649>(new FunctionControl649(control));
        _commandControl = QSharedPointer<CommandControl649>(new CommandControl649());
        _paramsController = QSharedPointer<ParamsController649>(new ParamsController649());
        break;
    }

    case 330:
    case 344:
    case 345:
    case 346:
    {
        _functionControl = QSharedPointer<FunctionControl330>(new FunctionControl330(control));
        break;
    }

    default:
    {
        _functionControl = QSharedPointer<InfoFunctionControl>(new InfoFunctionControl(control));
        break;
    }

    }

    if(params.getNumberKA() == 649)
    {
        _commandControl = QSharedPointer<CommandControl>(new CommandControl());
        _paramsController = QSharedPointer<ParamsController>(new ParamsController());
    }

    setCommonParams();
}

void FactoryParamsCMS::setCommonParams()
{
    auto strct = params.getInfoFC()->getOldParams();
    _functionControl->setParamsPreviousCMS(strct);
    params.setInfoFC(_functionControl);

    if(_commandControl)
    {
        _commandControl->setCurrentMode(params.getCommands().getCurrentMode());
        _commandControl->setNumKA(params.getCommands().numKA());
        _commandControl->setParamsSession(params.getCommands().getParamsSession().numberSeans, params.getCommands().getParamsSession().numberVitok);
        params.setCommands(_commandControl);
    }
}
