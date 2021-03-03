#include "linkingFcc/FileWorker/BaseFileWorker.h"

BaseFileWorker::BaseFileWorker()
{
    QDir dir = QDir::currentPath();
    dir.cd(pathFiles);
    filePath = dir.absolutePath();
}

BaseFileWorker::~BaseFileWorker()
{
    if(file.isOpen())
        file.close();
}

void BaseFileWorker::setNameFile(const QString &name)
{
    if(!name.isEmpty())
        file.setFileName(dir.absolutePath() + "/" + name);
}

QByteArray BaseFileWorker::read()
{
    QByteArray array;

    if(!file.exists())
        return array;

    if(file.open(QIODevice::ReadOnly))
    {
        array = file.readAll();
        file.close();
    }

    return array;
}

const QString BaseFileWorker::path() const
{
    return file.fileName();
}

const QString BaseFileWorker::absolutePathDir()
{
    return dir.absolutePath();
}
