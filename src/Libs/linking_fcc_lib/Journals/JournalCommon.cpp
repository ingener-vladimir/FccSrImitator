#include "linkingFcc/Journals/JournalCommon.h"

QJsonArray JournalCommon::getLogs()
{
    QJsonArray array;
    QMutexLocker lock(&_mutex);
    for(auto& log : _events)
        array.append(QJsonValue(log));
    _events.clear();
    return array;
}

bool JournalCommon::isEmpty()
{
    QMutexLocker lock(&_mutex);
    return _events.isEmpty();
}

void JournalCommon::writeEvent(const QString &event)
{
    if(event.isEmpty())
        return;

    QMutexLocker lock(&_mutex);
    QDateTime dt = QDateTime::currentDateTime();
    auto def = dt.toSecsSinceEpoch() - _time;
    if(_time > 0 && def < 1)
        dt = QDateTime::fromSecsSinceEpoch(_time);

    QString str = "|" + dt.date().toString("dd.MM") + "|" + dt.time().toString("hh:mm:ss") + "| " + event;
    _events.append(str);
}

void JournalCommon::setTime(uint64_t time)
{
    QMutexLocker lock(&_mutex);
    _time = time;
}
