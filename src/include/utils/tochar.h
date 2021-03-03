#ifndef TOCHAR_H
#define TOCHAR_H
#include <qglobal.h>
// Эти функции определены в заголовочном файле, потому что они не делают абсолютно ничего и должны инлайниться. Они нужны, потому что QByteArray использует char и стандарт говорит, что если мы приводим unsigned char>127 к char, результат зависит от реализации.
// Функция fromChar не нужна при приведении char к uchar, но необходима, если мы хотим склеить число из байтов. Например, в следующем коде
/* char c = 128;
 * int a = c;
 */
// a может быть равно 128 или -1 (или теоретически даже 127, хотя на самом деле никогда оно не будет равно 127)
namespace functions {
    inline char toChar(quint8 byte) {
        return *(reinterpret_cast<char*>(&byte));
    }
    inline quint8 fromChar(char character) {
        return *(reinterpret_cast<quint8*>(&character));
    }
}
#endif // TOCHAR_H
