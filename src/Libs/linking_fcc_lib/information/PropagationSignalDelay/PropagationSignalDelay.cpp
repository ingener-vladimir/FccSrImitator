#include "linkingFcc/infornation/PropagationSignalDelay/PropagationSignalDelay.h"
#include "utils/DateTimeUtils.h"

void PropagationSignalDelay::unserialize(const QByteArray &array)
{
    if(array.size() < 16)
        return;

    quint64 dateTime = array.mid(0, 6).toLongLong();
    _dateTime = QDateTime::fromSecsSinceEpoch(dateTime);
    _value = array.mid(8).toDouble();
}

QByteArray PropagationSignalDelay::serialize() const
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out.setByteOrder(QDataStream::LittleEndian);

    quint64 dt = _dateTime.toSecsSinceEpoch();
    out << (dt & 0xffff);
    out << ((dt >> 16) & 0xffff);
    out << ((dt >> 32) & 0xffff);
    out << ((dt >> 48) & 0xffff);
    array.append(QString::number(_value).rightJustified(8, '0'));
    return array;
}

double PropagationSignalDelay::getValue() const
{
    return _value;
}

void PropagationSignalDelay::setValue(double value)
{
    _value = value;
}

QDateTime PropagationSignalDelay::getDateTime() const
{
    return _dateTime;
}

void PropagationSignalDelay::setDateTime(const QDateTime &dateTime)
{
    _dateTime = dateTime;
}


