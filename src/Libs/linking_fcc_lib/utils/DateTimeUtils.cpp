#include "utils/DateTimeUtils.h"

// TDateTime имеет формат DOUBLE, при этом целая часть – число полных суток с 30.12.1899,
// дробная - СС / (86400*1000000), где СС - число микросекунд, прошедшее с начала текущих суток,
quint64 DateTimeUtils::formatTDateTime(QDateTime tDateTime)
{
    static const double UnixStartDate = 25569.0; // 01/01/1970
    static const int UTCshift = 10800;
    double delphiTime = (((double)tDateTime.toSecsSinceEpoch() + UTCshift) / 86400.0) + UnixStartDate;
    quint64 res = 0;
    memcpy(&res, &delphiTime, sizeof(quint64));
    return res;

}

quint64 DateTimeUtils::formatTDateTime(quint64 time)
{
    static const double UnixStartDate = 25569.0; // 01/01/1970
    static const int UTCshift = 10800;
    double delphiTime = (((double)time + UTCshift) / 86400.0) + UnixStartDate;
    quint64 res = 0;
    memcpy(&res, &delphiTime, sizeof(quint64));
    return res;

}

QDateTime DateTimeUtils::parseTDateTime(QString tDateTime)
{
    double tDateTimeDouble = tDateTime.toDouble();
    uint64_t msecsDays = uint16_t(tDateTimeDouble) * DAY_SECONDS - 2 * DAY_SECONDS;
    uint64_t mSecsSinceDay = double(tDateTimeDouble - uint16_t(tDateTimeDouble)) * DAY_SECONDS * 1000;
    return  QDateTime::fromMSecsSinceEpoch(msecsDays + mSecsSinceDay);
}
