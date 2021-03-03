#ifndef BYTEARRAYUTILS_H
#define BYTEARRAYUTILS_H

#include <QByteArray>
#include <climits>

class ByteArrayUtils
{
    ByteArrayUtils() {}
public:
    template<typename Integral>
    static QByteArray toByteArrayLE(Integral integral)
    {
    // тут можно сделать static_assert, что Integral - это целочисленный тип.
    // значение побитового сдвига с отрицательным левым операндом типа implementation-defined,
    // но на самом деле это везде арифметический сдвиг
    // порядок байтов не влияет на побитовый сдвиг, так написано в стандарте.
        QByteArray res;
        for(unsigned int i = 0; i < sizeof(Integral); i++)
        {
            res.append((quint8)(integral & 0xFF));
            integral >>= CHAR_BIT; // если Integral - это char, то здесь unspecified behavior, но мы потом нигде не используем integral
        }
        return res;
    }
};

#endif // BYTEARRAYUTILS_H
