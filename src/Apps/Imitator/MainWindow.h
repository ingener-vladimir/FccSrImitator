#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QList>
#include <QString>
#include <QTimer>

#include "linkingFcc/LinkingFCC.h"

static QList<QString> commandsWithParams
{
    {"1007"},
    {"1009"},
    {"1010"},
    {"1013"},
    {"1014"},
    {"1015"},
    {"1023"},
    {"1024"},
    {"1029"},
    {"1031"}
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QSharedPointer<LinkingFCC> _linkingFCC{nullptr};
    QTimer _timerUpdate;
    QByteArray _arryaSpecialInformation;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_SingleCommand_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void updateParameters();
private:
    Ui::MainWindow *ui;
    void addNewPackage(QByteArray &array, TypeInfo typeInfo);
    QByteArray readFile(QString &filePath);
};

#endif // MAINWINDOW_H
