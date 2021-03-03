/*!
    \file
    \brief Интерфейсный класс для работы с параетрами устройства
    \author Данильченко Артем
    \version 0.1
    \date июль 2019 г.
*/

#ifndef IDEVICEPARAM_H
#define IDEVICEPARAM_H

#include <QByteArray>
#include <QSharedPointer>
#include <stdint.h>
#include <QObject>
#include <QMap>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#define _NAME_OF_ARG(ARG) #ARG

namespace daq
{

class IDeviceParam
{

public:
    virtual  ~IDeviceParam() {}
    /*!
     *   \brief сериализация параметров устроства в формат json
     *   \param[out] json документ
     */
    virtual QJsonArray serializeToJSON() = 0;
    /*!
     *   \brief сериализация параметров устроства в бинарный формат
     *   \param[out] массив байт.
     */
    virtual QByteArray serializeToBin() = 0;
    /*!
     *   \brief распаковка параметров устройства во внутренный формат из
     *          json. Для реализации имитаторов
     *   \param[in] json документ
     */
    virtual bool unserializeFromJSON(const QJsonDocument &) = 0;

protected:
    enum JsonType
    {
        BOOLEAN = 0,
        INTEGER,
        DOUBLE,
        STRING,
        LISTVAR,
        LISTSTR,
        HEXDATA,
        OCTDATA,
        LISTERR
    };
    const QMap<int,QString> mapJsonType = { { BOOLEAN,QString("boolean") },
                                            { INTEGER, QString("integer") },
                                            { DOUBLE, QString("double") },
                                            { STRING, QString("string")},
                                            { LISTVAR, QString("listvar")},
                                            { LISTSTR, QString("liststr")},
                                            { HEXDATA, QString("hexdata")},
                                            { OCTDATA, QString("octdata")},
                                            { LISTERR, QString("tablerr")}
                                          };

    enum AccessType
    {
        READ_TYPE = 0,
        WRITE_TYPE,
        READ_WRITE_TYPE
    };

    const QMap<int, QString> mapAccessType = { { READ_TYPE, QString("r") },
                                               { WRITE_TYPE, QString("w") },
                                               { READ_WRITE_TYPE, QString("rw") }
                                             };
};
}
#endif // IDEVICEPARAM_H
