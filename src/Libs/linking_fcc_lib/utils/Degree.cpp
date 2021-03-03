#include "utils/Degree.h"

using namespace daq;

Degree::Degree(double decDegree)
{
    fromDouble(decDegree);
}

void Degree::fromDWORD(const quint32 &wgrad, const quint16 &cmr)
{
    _negativeSign = false;
    if(wgrad < 0)
        _negativeSign = true;

    div_t g_div = div(qAbs(wgrad * cmr), 3600);
    _grad = g_div.quot;
    div_t m_div = div(qAbs(g_div.rem), 60);
    _min = m_div.quot;
    _sec = m_div.rem;
}

void Degree::fromWORD(const qint32 &wgrad, const quint16 &cmr)
{
    _negativeSign = false;
    if(wgrad < 0)
        _negativeSign = true;

    div_t g_div = div(qAbs(wgrad * cmr), 3600);
    _grad = qAbs(g_div.quot);// * (wgrad < 0 ? -1 : 1);
    div_t m_div = div(qAbs(g_div.rem), 60);
    _min = m_div.quot;
    _sec = m_div.rem;
}

void Degree::fromDouble(double decDegree, const uint16_t& cmr)
{
    _negativeSign = false;
    if(decDegree < 0)
        _negativeSign = true;

    decDegree = qAbs(decDegree * cmr);
    auto mapDegree = modf(decDegree);
    auto mapMin = modf(mapDegree.values().at(0) * 60);
    auto mapSec = modf(mapMin.values().at(0) * 60);
    _grad = mapDegree.keys().at(0);
    _min = mapMin.keys().at(0);
    _sec = mapSec.keys().at(0);
}

QMap<int, double> Degree::modf(const double value)
{
    QMap<int, double> mapValues;
    QStringList list = QString::number(value, 'g', 10).split(".");
    if(list.size() > 1)
        list[1] = "0." + list[1];
    else
        list.append("0");
    auto intValue = list.at(0).toInt();
    auto frac = list.at(1).toDouble();
    mapValues.insert(intValue, frac);

    return mapValues;
}

double Degree::toDouble()const
{
    double degree = (double)(_grad + 1 / 60.0 * _min + 1 / 3600.0 * _sec);
    if (negativeSign())
        degree = -degree;

    return degree;
}

QString Degree::toString() const
{
    QString res{""};
    if(_negativeSign)
        res.append("-");
    return res + QString("%1%2%3'%4\"").arg(_grad, 3, 10, QChar('0'))
                                       .arg(QString(0x00b0))
                                       .arg(_min, 2, 10, QChar('0'))
                                       .arg(_sec, 2, 10, QChar('0'));
}

int16_t Degree::grad() const
{
    return _grad;
}

void Degree::setGrad(const int16_t &grad)
{
    if (grad >= 0 && grad < MAX_GRAD)
        _grad = grad;

    if (grad == MAX_GRAD){
        _grad = grad;
        _min = 0;
        _sec = 0;
    }

    if (grad > MAX_GRAD)
        _grad = 0;

    if (grad < 0)
        setGrad(MAX_GRAD);
}

int16_t Degree::min() const
{
    return _min;
}

void Degree::setMin(const int16_t &min)
{
    if (min >= 0 && _min <= MAX_MIN)
        _min = min;

    if (min > MAX_MIN)
        _min = 0;

    if (min < 0)
        _min = MAX_MIN;
}

int16_t Degree::sec() const
{
    return _sec;
}

void Degree::setSec(const int16_t &sec)
{
    if (sec >= 0 && sec <= MAX_SEC)
        _sec = sec;

    if (sec > MAX_SEC)
        _sec = 0;

    if (sec < 0)
        _sec = MAX_SEC;
}

bool Degree::negativeSign() const
{
    return _negativeSign;
}

void Degree::setNegativeSign(bool negativeSign)
{
    _negativeSign = negativeSign;
}
