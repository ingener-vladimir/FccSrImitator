#include "linkingFcc/FileWorker/Controllers/ControllerTargetDesignation.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

QString ControllerTargetDesignation::findLastTargetDesignation(int KA)
{
    FileWorkerTD worker;
    auto path = worker.absolutePathDir();

    QDir workDir(path);

    QStringList nameFilter{"*.cu"};
    QFileInfoList list = workDir.entryInfoList(nameFilter, QDir::Files ); // сказываем что нас интересуют только файлы

    QFileInfo fileinfo; // сюда будем считывать элементы
    qint64 secs{0};
    QString lastFilePath;
    foreach (fileinfo, list) // foreach - приятный подарок-макрос от Qt =)
    {
        auto fileName = fileinfo.fileName();

        qDebug() << "[TD] check TD:" << fileName << "for KA:" << KA;

        if(!validateTargetDestination(fileinfo.absoluteFilePath(), KA).isEmpty()) continue;

        fileName.chop(3);
        auto lastDate = QDateTime::fromString(fileName, "dd.MM.yyyy hh:mm:ss");
        auto lastSecs = lastDate.toSecsSinceEpoch();
        qDebug() << "[TD] date:" << lastDate << "time:" << lastSecs << KA;
        if((QDateTime::currentSecsSinceEpoch() - lastSecs) > MAX_COUNT_SECS)
            continue;
        if(lastSecs > secs)
        {
            secs = lastSecs;
            lastFilePath = fileinfo.absoluteFilePath();
        }
    }

    qDebug() << "[TD] find file:" << lastFilePath;
    return lastFilePath;
}

QString ControllerTargetDesignation::validateTargetDestination(const QString &array, int KA) {

    qDebug() << "[TD]" << array;

    QByteArray arrayRead;
    QFile file(array);
    if(file.open(QIODevice::ReadOnly)) {
        arrayRead = file.readAll();
    }

    if(!arrayRead.isEmpty()) {
        qint64 startT = 0, endT = 0;
        uint32_t kaNum = 0;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(arrayRead);
        if(jsonDoc.isNull() || jsonDoc.isEmpty())
            jsonDoc = QJsonDocument::fromBinaryData(arrayRead);

        if(!jsonDoc.isNull() && !jsonDoc.isEmpty()) {
            QJsonObject root = jsonDoc.object();
            QJsonArray jsonArray = root.value("arrayTD").toArray();

            static const QString dateTimeFormat = "dd/MM/yyyy hh:mm:ss";

            //get start time
            {
                QJsonObject obj1 = jsonArray[0].toObject();
                QString dtStr1 = obj1.value("date").toString();
                dtStr1.append(" ");
                dtStr1.append(obj1.value("time").toString());
                QDateTime dt1 = QDateTime::fromString(dtStr1, dateTimeFormat);
                startT = dt1.toSecsSinceEpoch();
            }

            //get end time
            {
                QJsonObject obj1 = jsonArray[jsonArray.size() - 1].toObject();
                QString dtStr1 = obj1.value("date").toString();
                dtStr1.append(" ");
                dtStr1.append(obj1.value("time").toString());
                QDateTime dt1 = QDateTime::fromString(dtStr1, dateTimeFormat);
                endT = dt1.toSecsSinceEpoch();
            }

            //get ka
            QJsonValue jv = root.value("numberKA");
            kaNum = jv.toInt();

            //check
            qint64 currentT = QDateTime::currentDateTime().toSecsSinceEpoch();

            if(currentT > endT) {
                file.remove();
                qDebug( ) << "[TD] dtEnd:" << endT << "dtStart:" << startT << "dtCurrent" << currentT;
                return QString("Получены просроченные ЦУ для КА %1").arg(kaNum);
            }

            if(KA != kaNum) {
                return QString("Получены ЦУ для другого КА %1").arg(kaNum);
            }
        }
    } else return QString("Файл ЦУ КА %1 не найден").arg(KA);

    return "";
}
