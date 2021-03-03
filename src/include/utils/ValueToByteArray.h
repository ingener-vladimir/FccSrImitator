#ifndef VALUETOBYTEARRAY_H
#define VALUETOBYTEARRAY_H
#include "tochar.h"
#undef LIBAPP_EXPORTS
#ifdef DAQ_MAKE_DLL
#define LIBAPP_EXPORTS
#endif

#include <QByteArray>
#include <QByteArray>
#include <climits>
namespace functions {

template<typename Integral>
QByteArray toByteArrayLE(Integral integral)
{
    // тут можно сделать static_assert, что Integral - это целочисленный тип.
    // значение побитового сдвига с отрицательным левым операндом типа implementation-defined,
    // но на самом деле это везде арифметический сдвиг
    // порядок байтов не влияет на побитовый сдвиг, так написано в стандарте.
    QByteArray res;
    for(unsigned int i = 0; i < sizeof(Integral); i++)
    {
        res.append((quint8)(integral&0xFF));
        integral >>= CHAR_BIT; // если Integral - это char, то здесь unspecified behavior, но мы потом нигде не используем integral
    }
    return res;
}
template<typename Integral>
static QByteArray toByteArrayBE(Integral integral)
{
    QByteArray res;
    for(unsigned int i = sizeof(Integral); i >0 ; i--)
    {
        res.append((quint8)((integral >> ((i-1)*CHAR_BIT))&0xFF));
    }
    return res;
}

//QByteArray  quint32ToByteArray(quint32 _val); это BE

union  f_union{
    char u_byte[4];
    float u_float;
    quint32 u_int;
};

quint32 byte4ToUint(const QByteArray& _arr, quint16 _offs); // я не заменяю эти функции своей офигенной функцией, потому что не уверен,
/*qint32 byte4ToInt(const QByteArray& _arr, quint16 _offs);*///с какого конца они пишут число (хотя на интеле вроде всегда со старшего)
// эти функции используют undefined behavior, а моя функция всё делает по стандарту, поэтому я боюсь, что поведение проги может
// измениться, если я заменю эти ужасные функции на getNumberBE (которая не написана)

float  byte4ToFloat(const QByteArray &_arr, quint16 _offs);
float  byte4ToFloatPDPE(const QByteArray &_arr, quint16 _offs);
qint32  byte4ToIntBE(const QByteArray &_arr, quint16 _offs);
qint32  byte4ToIntLE(const QByteArray &_arr, quint16 _offs);

//QByteArray  qint32ToByteArray(qint32 _val); это BE

void  addWordBE(QByteArray* _arr,quint16 _data);
void  addWordLE(QByteArray* _arr, quint16 _data);
void  addDWordBE(QByteArray* _arr, quint32 _data);
void  addDWordLE(QByteArray* _arr,quint32 _data);
void  addIntLE(QByteArray* _arr, qint32 _data);
void  addFloatLE(QByteArray* _arr, float _data);

qint16  toInt16BE(char _a, char _b);
quint16  toInt16LE(char _a, char _b);

template<typename Integral> Integral getNumberLE(const QByteArray& array, int index)
{ // конечно же тут наверное будет loop unrolling надеюсь
    using functions::fromChar;
    Integral res{0};
    for(uint i = 0; i < sizeof(Integral); i++) {
        res |= ((static_cast<Integral>(fromChar(array[index+i]))) << i*CHAR_BIT);
    }
    return res;
}
}
#endif // VALUETOBYTEARRAY_H
