#ifndef DATETIMEUTILS_H
#define DATETIMEUTILS_H

#include <QDateTime>
#include <QString>

class DateTimeUtils
{
    DateTimeUtils() {}

    static const uint32_t DAY_SECONDS = 86400;
public:
    static quint64 formatTDateTime(QDateTime tDateTime);
    static QDateTime parseTDateTime(QString tDateTime);
    quint64 formatTDateTime(quint64 time);
};

#endif // DATETIMEUTILS_H
