#ifndef DEGREE_H
#define DEGREE_H

#include <QString>
#include <QMap>
#include <QChar>
#include <QDebug>
#include <stdint.h>
#include <math.h>

namespace daq
{

class Degree
{
    int16_t _grad{0};
    int16_t _min{0};
    int16_t _sec{0};
    bool _negativeSign{false};

    const int16_t MAX_GRAD = 360;
    const int16_t MAX_MIN = 59;
    const int16_t MAX_SEC = 59;

public:
    Degree() {}
    Degree(double decDegree);

    void fromDouble(double radian, const uint16_t &cmr = 1);
    double toDouble() const;

    void fromDWORD(const quint32& wgrad, const quint16& cmr);
    void fromWORD(const qint32& wgrad, const quint16& cmr);

    QString toString() const;

    int16_t grad() const;
    void setGrad(const int16_t &grad);

    int16_t min() const;
    void setMin(const int16_t &min);

    int16_t sec() const;
    void setSec(const int16_t &sec);

    bool negativeSign() const;
    void setNegativeSign(bool negativeSign);

private:
    QMap<int, double> modf(const double value);
};

}


#endif // DEGREE_H
