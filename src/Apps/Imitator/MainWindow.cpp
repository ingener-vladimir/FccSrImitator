#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QString>
#include <QFileDialog>
#include <QDir>

#include "linkingFcc/infornation/SingleCommand/fcc_sr/SingleCommandSr.h"
#include "linkingFcc/infornation/CommandControl/fcc-sr/ControlCommandSr.h"
#include "utils/DateTimeUtils.h"
#include "linkingFcc/infornation/Params/fcc-sr/ParamsSr.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dateTimeEdit_3->hide();

    _linkingFCC = QSharedPointer<LinkingFCC>(new LinkingFCC());
    _linkingFCC->createClient("127.0.0.1", 9090, TypeFactory::FCC_SR);

    QObject::connect(&_timerUpdate, &QTimer::timeout,
                     this, &MainWindow::updateParameters);

    _timerUpdate.start(1000);
}

MainWindow::~MainWindow()
{
    _timerUpdate.stop();
    delete ui;
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    ui->dateTimeEdit_3->hide();
    ui->lineEdit_5->show();
    if(commandsWithParams.contains(arg1))
    {
        ui->lineEdit_5->show();
        ui->lineEdit_5->setEnabled(true);
    }
    else if(arg1 == "1019")
    {
        ui->lineEdit_5->hide();
        ui->dateTimeEdit_3->show();
        ui->dateTimeEdit_3->move(ui->lineEdit_5->x() + 90, ui->lineEdit_5->y());
    }
    else
        ui->lineEdit_5->setEnabled(false);
}

void MainWindow::on_pushButton_SingleCommand_clicked()
{
    uint16_t code = ui->lineEdit_SingleCommand->text().toInt();
    Periodicity periodecity = (Periodicity)ui->comboBox_SingleCommand->currentIndex();
    SingleCommandSr singleCommand(periodecity, code);
    QByteArray array = singleCommand.serialize();
    addNewPackage(array, TypeInfo::INFO_2002);
}

void MainWindow::on_pushButton_clicked()
{
    SpecialInformationSr specialInformationSr(ui->lineEdit_25->text().toInt());
    specialInformationSr.setConvertPhrase(_arryaSpecialInformation);
    QByteArray serializedArray = specialInformationSr.serialize();
    addNewPackage(serializedArray, TypeInfo::INFO_2001);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Выбор файла СИ", "", "*.bit");
    _arryaSpecialInformation = readFile(str);
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->comboBox_2->currentIndex() == 0)
        return;

    QString numberCommand = ui->comboBox_2->currentText();
    uint16_t number = numberCommand.toInt();
    ControlCommandSr controlCommandSr((ControlCommands)number);
    if(commandsWithParams.contains(numberCommand))
    {
        uint16_t param = ui->lineEdit_5->text().toInt();
        if(numberCommand == "1009")
            param *= 10;
        controlCommandSr.addWords(param);
    } else if(numberCommand == "1019")
    {
        QString dtStr = ui->dateTimeEdit_3->text();
        QDateTime dt = QDateTime::fromString(ui->dateTimeEdit_3->text(), "dd.MM.yyyy HH:mm:ss");
        quint64 dtr = DateTimeUtils::formatTDateTime(dt);
        quint16 word1 = dtr & 0xffff;
        quint16 word2 = (dtr >> 16) & 0xffff;
        quint16 word3 = (dtr >> 32) & 0xffff;
        quint16 word4 = (dtr >> 48) & 0xffff;
        controlCommandSr.addWords(word1, word2, word3, word4);
    }
    QByteArray array = controlCommandSr.serialize();
    addNewPackage(array, TypeInfo::INFO_2003);
}

void MainWindow::addNewPackage(QByteArray &array, TypeInfo typeInfo)
{
    _linkingFCC->packageController()->getFactory()->addPackage(array, typeInfo);
}

void MainWindow::updateParameters()
{
    ParamsSr& paramsSr = ParamsSrSingleton::getInstance();

    // задержка распространения сигнала
    ui->dateTimeEdit->setDateTime(paramsSr.getPropagationSignalDelay().getDateTime());
    ui->lineEdit->setText(QString::number(paramsSr.getPropagationSignalDelay().getValue()));

    // доплеровское смещения частоты
    ui->dateTimeEdit_2->setDateTime(paramsSr.getDoplerFrequencyOffset().getDateTime());
    ui->lineEdit_2->setText(QString::number(paramsSr.getDoplerFrequencyOffset().getValue()));

    // тедеметрия
    ui->lineEdit_3->setText(QString::number(paramsSr.getFunctionControlSr().getCounterTelemetry()));
    ui->textEdit->setPlainText(paramsSr.getTelemetry().information());

    // информация функционального контроля
    ui->lineEdit_6->setText(QString::number(paramsSr.getFunctionControlSr().getOffsetTime()));
    ui->lineEdit_11->setText(QString::number(paramsSr.getFunctionControlSr().getLiterOTC()));
    ui->lineEdit_9->setText(QString::number(paramsSr.getFunctionControlSr().getDoplerCorrection()));
    ui->lineEdit_7->setText(QString::number(paramsSr.getFunctionControlSr().getLiter()));
    ui->lineEdit_8->setText(QString::number(paramsSr.getFunctionControlSr().getBandReceiver()));
    ui->lineEdit_10->setText(QString::number(paramsSr.getFunctionControlSr().getLiterPNS()));
    ui->lineEdit_15->setText(QString::number(paramsSr.getFunctionControlSr().getSignalPower()));

    ui->checkBox->setChecked(paramsSr.getFunctionControlSr().getConnectionState());
    ui->checkBox_2->setChecked(paramsSr.getFunctionControlSr().getWorkModeState());
    ui->checkBox_3->setChecked(paramsSr.getFunctionControlSr().getImitationPchState());
    ui->checkBox_4->setChecked(paramsSr.getFunctionControlSr().getReadyCmosState());
    ui->checkBox_5->setChecked(paramsSr.getFunctionControlSr().getOnPshstate());
    ui->checkBox_6->setChecked(paramsSr.getFunctionControlSr().getArchiveState());

    ui->checkBox_7->setChecked(paramsSr.getFunctionControlSr().getZeroTicketSi());
    ui->checkBox_8->setChecked(paramsSr.getFunctionControlSr().getMinusTicketSi());
    ui->checkBox_9->setChecked(paramsSr.getFunctionControlSr().getPlusTicketSi());
    ui->checkBox_10->setChecked(paramsSr.getFunctionControlSr().getProcessTicketSi());
    ui->checkBox_11->setChecked(paramsSr.getFunctionControlSr().getOnTicketSi());
    ui->lineEdit_13->setText(QString::number(paramsSr.getFunctionControlSr().getNumberTicketedSI()));
    ui->lineEdit_14->setText(QString::number(paramsSr.getFunctionControlSr().getIdSI()));

    ui->checkBox_12->setChecked(paramsSr.getFunctionControlSr().getZeroTicketOtc());
    ui->checkBox_13->setChecked(paramsSr.getFunctionControlSr().getPlusTicketOtc());
    ui->checkBox_14->setChecked(paramsSr.getFunctionControlSr().getProcessTicketOtc());
    ui->lineEdit_12->setText(QString::number(paramsSr.getFunctionControlSr().getNumberTicketedOTC()));

    ui->checkBox_15->setChecked(paramsSr.getFunctionControlSr().getOneModeTelemetry());
    ui->checkBox_16->setChecked(paramsSr.getFunctionControlSr().getEightModeTelemetry());
    ui->checkBox_17->setChecked(paramsSr.getFunctionControlSr().getThirtyTwoTicketSi());
    ui->lineEdit_24->setText(QString::number(paramsSr.getFunctionControlSr().getCounterTelemetry()));

    ui->checkBox_18->setChecked(paramsSr.getFunctionControlSr().getModulationPch());
    ui->checkBox_19->setChecked(paramsSr.getFunctionControlSr().getFzsPch());
    ui->checkBox_20->setChecked(paramsSr.getFunctionControlSr().getConvertatorPch());

    ui->checkBox_21->setChecked(paramsSr.getFunctionControlSr().getDecoderPk1());
    ui->checkBox_22->setChecked(paramsSr.getFunctionControlSr().getDecoderPk2());
}

QByteArray MainWindow::readFile(QString& filePath)
{
    QByteArray array;
    if(filePath.isEmpty())
        return array;

    QFile file;
    file.setFileName(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        array = file.readAll();
        file.close();
    }

    return array;
}

