#include "linkingFcc/FileWorker/FileWorkerTD.h"

FileWorkerTD::FileWorkerTD()
{
    QDir workDir = QDir::currentPath();
    workDir.setPath(filePath + dirInternal);

    // если каталога нет, он создастся
    if(!workDir.exists())
        workDir.mkpath(".");

    QDir dataDir;
    dataDir.setPath(workDir.absolutePath() + dirTD);

    // если каталога нет, он создастся
    if(!dataDir.exists())
        dataDir.mkpath(".");

    dir.setPath(dataDir.absolutePath());
    setNameFile(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")
                + expansion);
}

bool FileWorkerTD::write(const QByteArray &data)
{
    bool res{false};
    if(file.open(QIODevice::WriteOnly))
    {
        res = file.write(getDataFormatJson(data));
        file.flush();
        file.close();
    }

    QDir workDir = QDir::currentPath();
    workDir.setPath(pathFiles + pathOutTD);

    // если каталога нет, он создастся
    if(!workDir.exists())
        workDir.mkpath(".");

    QFile fileOut(workDir.absolutePath() + "/" +
                  QDateTime::currentDateTime().toString("dd:MM:yyyy_hh:mm:ss") +
                  expansion);

    if(fileOut.open(QIODevice::WriteOnly))
    {
        fileOut.write(data);
        fileOut.flush();
        fileOut.close();
    }

    return res;
}

QByteArray FileWorkerTD::getDataFormatJson(const QByteArray& array)
{
    if(array.contains("arrayTD"))
        return array;

    QString line = array.left(array.indexOf(inputLineTerminator));
    static const QRegularExpression regexp(".*=[^\\d]*(\\d+).*=[^\\d]*(\\d+).*");
    regexp.optimize();
    QRegularExpressionMatch match = regexp.match(line);
    auto equally = line.indexOf(QChar('='));
    auto space = line.indexOf(QChar(' '));
    auto ka = line.mid(equally + 1, space - equally).toInt();

    QByteArray tinyChunk(array.right(array.size() - array.indexOf(inputLineTerminator) - inputLineTerminator.length()));
    QJsonArray arrayJson;

    QJsonObject object;
    object.insert("numberKA", QJsonValue(ka));

    while(tinyChunk.indexOf(inputLineTerminator) != -1)
    {
        QByteArray line = tinyChunk.left(tinyChunk.indexOf(inputLineTerminator));
        arrayJson.append(parseLineTD(line));
        tinyChunk = tinyChunk.right(tinyChunk.size() - tinyChunk.indexOf(inputLineTerminator) - inputLineTerminator.length());
    }

    object.insert("arrayTD", arrayJson);

    QJsonDocument doc(object);
    return doc.toJson(QJsonDocument::Indented);
}

QJsonObject FileWorkerTD::parseLineTD(const QByteArray& line)
{
    QJsonObject object;
    // Целеуказания приходят в этом виде
    //    "15/07/2017 | 23:30:00 | 238 36 55 | 10 53 25[ | 40500.844[ |-0.000006]];\r\n";
    //   , где | - это вертикальная черта, а [ ]  - это опционально

    QDateTime dateTime = QDateTime::fromString(line.left(21), formatDateTime);
    object.insert("date", QJsonValue(dateTime.date().toString("dd/MM/yyyy")));
    object.insert("time", QJsonValue(dateTime.time().toString("hh:mm:ss")));

    QTextStream stream(line.right(line.size() - 23), QIODevice::ReadOnly);
    double azg{0.}, azm{0.}, azs{0.};
    stream >> azg >> azm >> azs;
    double az = azg + azm / 60. + azs / (60. * 60.);
    object.insert("azimuth", QJsonValue(az));

    char dummy; // я в упор не увидел в документации способа пропустить символ из ввода получше
    stream >> ws >> dummy;
    double elg{0.}, elm{0.}, els{0.}, el{0.};
    if(dummy == '|')
    {
        stream >> elg >> elm >> els;
        el = elg + elm / 60. + els / (60. * 60.);
    }
    object.insert("elevation", QJsonValue(el));

    stream >> ws >> dummy;
    double range{0.};
    if(dummy == '|')
    {
        stream >> range;
        range *= 1000;
    }
    object.insert("distance", QJsonValue(range));

    stream >> ws >> dummy;
    double speed{0.};
    if(dummy == '|')
    {
        stream >> speed;
        speed *= 1000;
        object.insert("speed", QJsonValue(speed));
    }
    return object;
}


