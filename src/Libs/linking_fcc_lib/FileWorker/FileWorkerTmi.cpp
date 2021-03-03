#include "linkingFcc/FileWorker/FileWorkerTmi.h"

FileWorkerTmi::FileWorkerTmi()
{
    QDir workDir = QDir::currentPath();
    workDir.setPath(filePath + dirOut);

    // если каталога нет, он создастся
    if(!workDir.exists())
        workDir.mkpath(".");

    QDir dataDir;
    dataDir.setPath(workDir.absolutePath() + dirTmi);

    // если каталога нет, он создастся
    if(!dataDir.exists())
        dataDir.mkpath(".");

    dir.setPath(dataDir.absolutePath());
}

bool FileWorkerTmi::write(const QByteArray &data)
{
    bool res{false};
    QIODevice::OpenModeFlag flag{QIODevice::WriteOnly};
    if(file.exists())
        flag = QIODevice::Append;

    if(file.open(flag))
    {
        res = file.write(data);
        file.flush();
        file.close();
    }
    return res;
}
