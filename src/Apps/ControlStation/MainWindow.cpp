#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "linkingFcc/infornation/Params/fcc-sr/ParamsSr.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("СТАНЦИЯ");
    _linkingFCC.createServer(9090, TypeFactory::FCC_SR);

    QObject::connect(&_timer, &QTimer::timeout,
                     this, &MainWindow::update);

    _timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    ParamsSr& paramsSr = ParamsSrSingleton::getInstance();
    paramsSr.getFunctionControlSr().setCounterTelemetry(rand() % 100);
    paramsSr.getFunctionControlSr().setBandReceiver(rand() % 100);
    paramsSr.getFunctionControlSr().setLiter(rand() % 100);
    paramsSr.getFunctionControlSr().setLiterOTC(rand() % 100);
    paramsSr.getFunctionControlSr().setLiterPNS(rand() % 100);
}
