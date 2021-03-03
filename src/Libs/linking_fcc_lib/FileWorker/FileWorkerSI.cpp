#include "linkingFcc/FileWorker/FileWorkerSI.h"

FileWorkerSI::FileWorkerSI()
{
    QDir workDir = QDir::currentPath();
    workDir.setPath(filePath + dirInternal);

    // если каталога нет, он создастся
    if(!workDir.exists())
        workDir.mkpath(".");

    QDir dataDir;
    dataDir.setPath(workDir.absolutePath() + dirSI);

    // если каталога нет, он создастся
    if(!dataDir.exists())
        dataDir.mkpath(".");

    dir.setPath(dataDir.absolutePath());
    setNameFile("FileSI.bit");
}

bool FileWorkerSI::write(const QByteArray &data)
{
    bool res{false};
    if(file.exists())
    {
       QFile fileTime("time.bit");
       auto name = QFileInfo(file).absoluteFilePath();
       if(fileTime.open(QIODevice::WriteOnly))
       {
           res = fileTime.write(data);
           fileTime.flush();
           fileTime.close();
           file.remove();
           fileTime.copy(name);
           fileTime.remove();
       }
    }

    else if(file.open(QIODevice::WriteOnly))
    {
        res = file.write(data);
        file.flush();
        file.close();
    }
    return res;
}
