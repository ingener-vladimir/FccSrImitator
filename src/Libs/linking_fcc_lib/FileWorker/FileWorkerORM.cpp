#include "linkingFcc/FileWorker/FileWorkerORM.h"

#include <QDateTime>

FileWorkerORM::FileWorkerORM(TypeFileORM type)
{
    QDir direc;
    direc.setPath(filePath + dirOut);

    // если каталога нет, он создастся
    if(!direc.exists())
        direc.mkpath(".");

    QDir dataDir;
    if(type == TypeFileORM::DISTANCE)
        dataDir.setPath(direc.absolutePath() + dirDist);

    else if(type == TypeFileORM::ANGLES)
        dataDir.setPath(direc.absolutePath() + dirAng);

    // если каталога нет, он создастся
    if(!dataDir.exists())
        dataDir.mkpath(".");

    dir.setPath(dataDir.absolutePath());
}

bool FileWorkerORM::write(const QByteArray &data)
{
    bool res{false};
    if(file.exists())
        file.copy(file.fileName() + "_" + QDateTime::currentDateTime().toString("yy.MM.dd hh:mm:ss.zzz"));

    if(file.open(QIODevice::WriteOnly))
    {
        res = file.write(data);
        file.flush();
        file.close();
    }
    return res;
}
