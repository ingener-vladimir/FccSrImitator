#ifndef NETWORKPACKAGEUTILS_H
#define NETWORKPACKAGEUTILS_H

#include <QByteArray>

class NetworkPackageUtils final
{
    NetworkPackageUtils() {}

    static const uint8_t ENDER = 0x27;                  ///< Концевик  = 0x27
    static const uint8_t ESCAPE = 0x55;                 ///< Escape-символ
    static const uint8_t INVERT_ENDER = 0xD8;           ///< Инверсия
    static const uint8_t INVERT_ESCAPE = 0xAA;          ///< Инверсия
public:
    static QByteArray unescapeImcomingMessage(const QByteArray &array);
};

#endif // NETWORKPACKAGEUTILS_H
