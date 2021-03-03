#ifndef PROPAGATIONSIGNALDELAY_H
#define PROPAGATIONSIGNALDELAY_H

#include <QDataStream>
#include <QDateTime>

class PropagationSignalDelay
{
    QDateTime _dateTime = QDateTime::currentDateTime();
    double _value{0.};

public:
    PropagationSignalDelay() {}

    double getValue() const;
    void setValue(double value);

    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &dateTime);

    void unserialize(const QByteArray& array);
    QByteArray serialize() const;
};

#endif // PROPAGATIONSIGNALDELAY_H
