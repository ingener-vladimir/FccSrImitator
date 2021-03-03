#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QDebug>

#include "linkingFcc/Senders/TmiSender.h"
#include "utils/ValueToByteArray.h"

void SenderTmi::startSendingTmi(TmiFormat format)
{
    _format = format;
    _isSendingTmi = true;
}

void SenderTmi::stopSendingTmi()
{
    _isSendingTmi = false;
}

TmiFormat SenderTmi::format() const
{
    return _format;
}

QByteArray SenderTmi::createTmiPackage(const QJsonObject& messageObject)
{
    QByteArray pseudoframe = QByteArray::fromBase64(messageObject["tmiFrame"].toString().toUtf8());

    quint32 time = functions::getNumberLE<quint32>(pseudoframe, 0);
    quint8 kaIdentifier = pseudoframe[8];

    quint8 firstByte = 0;
    if(messageObject["tmi8kHz"].toBool()) {
        firstByte = ((pseudoframe[4] & 0x0E) << 4) | 0x01;
    }
    if(messageObject["tmi1kHz"].toBool()) {
        firstByte = 0;
        quint8 kss = pseudoframe[4];
        firstByte = ((kss & 0x0e) << 3 | 0x01);
    }

    QByteArray permutedBody = pseudoframe.mid(11*4, 128*4);

    QDateTime frameReceptionTime = QDateTime::fromMSecsSinceEpoch(messageObject["timeUTC_ms"].toVariant().toLongLong());

    if(permutedBody.size() < 128*4)  {
        qDebug() << "[TMI SENDER] WTF??? size=", permutedBody.size();
    }

    QByteArray body; body.reserve(permutedBody.size());
    for(int i = 0; i < permutedBody.size(); i+=4) {
        body.append(permutedBody[i+3]);
        body.append(permutedBody[i+2]);
        body.append(permutedBody[i+1]);
        body.append(permutedBody[i+0]);
    }

    QByteArray package;

    package.append(functions::toByteArrayLE<quint8>(firstByte));
    package.append(functions::toByteArrayLE<quint16>(QDate(1900, 1, 1).daysTo( frameReceptionTime.date())));
    if(messageObject["isAddTMIId"].toBool()) {//520
        package.append(functions::toByteArrayLE<quint32>(QDateTime::fromMSecsSinceEpoch(time*1000l + frameReceptionTime.time().msecsSinceStartOfDay() % 1000)
                                                         .toOffsetFromUtc(3*60*60)
                                                         .time().msecsSinceStartOfDay()));
    } else { //519
        package.append(functions::toByteArrayLE<quint32>(QDateTime::fromMSecsSinceEpoch(time*1000l)
                                                         .toOffsetFromUtc(3*60*60)
                                                         .time().msecsSinceStartOfDay()/1000));
    }
    //uint32_t(frameReceptionTime.time().msecsSinceStartOfDay() / 1000);
    if(messageObject["isAddTMIId"].toBool())
        package.append(kaIdentifier);
    package.append(body);

    return package;
}

QList<QByteArray> SenderTmi::createCurrentTmi(const QJsonObject& object,
                                              const int16_t ka,
                                              const int16_t seans,
                                              const int16_t vitok)
{
    QList<QByteArray> listTmi;
    if(!_isSendingTmi || !object.contains("array_data"))
        return listTmi;

    if(_numberKA != ka && _numberSeans != seans && _numberVitok != vitok)
    {
        _receptionTime = QDateTime::currentDateTime();
        _numberKA = ka;
        _numberSeans = seans;
        _numberVitok = vitok;
    }
    FileWorkerTmi file;
    file.setNameFile(QString::number(_numberKA) + "_"
                     + QString::number(_numberSeans) + "_"
                     + QString::number(_numberVitok) + "_"
                     + _receptionTime.toString("_d.M.yyyy_hh:mm:ss") + ".txt");

    for(const QJsonValue& messageValue : object["array_data"].toArray())
    {

        QJsonObject messageObject = messageValue.toObject();
        if(!messageObject.contains("tmiFrame") || !messageObject["tmiFrame"].isString())
            continue;

        QByteArray package = createTmiPackage(messageObject);
        listTmi.append(package);
        file.write(package);
    }

    return listTmi;
}

