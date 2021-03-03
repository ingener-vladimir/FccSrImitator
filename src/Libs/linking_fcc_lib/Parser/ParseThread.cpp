#include "linkingFcc/Parser/ParseThread.h"

ParseThread::ParseThread(TypeKit type,
                         const QString &uuid,
                         QSharedPointer<IJournal> journal,
                         SenderParamsStation *sender)
    : _uuid(uuid)
{
    _worker = QSharedPointer<ParseWorker>(new ParseWorker(type, journal, sender));
    _worker->moveToThread(&_thread);

    QObject::connect(&_thread, &QThread::started,
                     _worker.data(), &ParseWorker::initThread);

    QObject::connect(_worker.data(), &ParseWorker::finished,
                     &_thread, &QThread::quit);
}

ParseThread::~ParseThread()
{
    if(_thread.isRunning())
    {
        _thread.quit();
        _thread.wait();
    }
    _worker.reset();
    _worker = nullptr;
}

void ParseThread::run(const QString& uuid, const QJsonObject &object)
{
    if(_uuid == uuid)
    {
        if(_worker)
        {
            _worker->setJsonObject(object);
            if(!_thread.isRunning())
                _thread.start();
        }
    }
}

void ParseThread::setUuid(const QString &uuid)
{
    _uuid = uuid;
}
