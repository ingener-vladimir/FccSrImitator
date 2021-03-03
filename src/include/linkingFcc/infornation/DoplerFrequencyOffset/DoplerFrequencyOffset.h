#ifndef DOPLERFREQUENCYOFFSET_H
#define DOPLERFREQUENCYOFFSET_H

#include <QDateTime>
#include <QDataStream>

class DoplerFrequencyOffset
{
    QDateTime _dateTime = QDateTime::currentDateTime();
    double _value{0.};

public:
    DoplerFrequencyOffset();

    double getValue() const;
    void setValue(double value);

    void setDateTime(const QDateTime &dateTime);
    QDateTime getDateTime() const;

    void unserialize(const QByteArray& array);
    QByteArray serialize() const;
};

#endif // DOPLERFREQUENCYOFFSET_H
