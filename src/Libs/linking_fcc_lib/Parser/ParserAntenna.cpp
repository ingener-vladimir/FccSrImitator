#include "linkingFcc/Parser/ParserAntenna.h"
#include "utils/Degree.h"

#include <QString>

#define EPSILON 0.000001
quint32 fromValue(double _value)
{
    int signflag = _value >= 0 ? 1 : -1;
    double intpart;
    _value = fabs(_value);

    double m = modf(_value, &intpart);
    quint32 m_grad = intpart;

    double s = modf(m * 60.0 + EPSILON, &intpart);
    quint32 m_min = intpart;

    modf(s * 60.0 + EPSILON, &intpart);
    quint32 m_sec = intpart;

    quint32 res = m_grad * 3600 + m_min * 60 + m_sec;

    return res * signflag;
}

ParserAntenna::ParserAntenna(QSharedPointer<IJournal> journal)
    : BaseParser(journal)
{

}

void ParserAntenna::parseParams(const QJsonObject &obj)
{
    /// ДОС азимут
    QJsonValue jv = obj.value("azimuth");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setAzimuthFBS(jv.toDouble());

    /// программный азимут
    jv = obj.value("prog_azimuth");
    if(!jv.isUndefined()) {
        params.setAzimuthProgramm(jv.toDouble());
        params.getInfoFC()->getRefInfoControl()->setPointAzimuth(jv.toDouble());
    }

    /// ДОС угол места
    jv = obj.value("elevation");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setElevationFBS(jv.toDouble());

    /// программный угол места
    jv = obj.value("prog_elevation");
    if(!jv.isUndefined()) {
        params.setElevProgramm(jv.toDouble());
        params.getInfoFC()->getRefInfoControl()->setPointElevation(jv.toDouble());
    }

    /// наличие поправки
    jv = obj.value("isCorrection");
    if(!jv.isUndefined()) {
        params.setIsCorrection(jv.toBool());
        params.getInfoFC()->setModeANT(ModeANT::CORRECTION, jv.toBool());
    }

    /// поправка по азимуту
    jv = obj.value("correction_azimuth");
    if(!jv.isUndefined()) {
        params.getInfoFC()->getRefInfoControl()->setCorrectionAzimuth(jv.toDouble());
    }

    bool isCalibrationMode = false;
    jv = obj.value("calibrationMode");
    if(!jv.isUndefined()) {
        isCalibrationMode = jv.toBool();
        params.setCalibrationMode(isCalibrationMode);
        params.getInfoFC()->setModeANT(ModeANT::CALIBRATION, jv.toBool());
    }

    jv = obj.value("current_mode");
    if(!jv.isUndefined()) {

        //params.getInfoFC()->setModeANT(ModeANT::CORRECTION, false);
        params.getInfoFC()->setModeANT(ModeANT::MANUAL, false);
        params.getInfoFC()->setModeANT(ModeANT::TD, false);
        params.getInfoFC()->setModeANT(ModeANT::PROGRAMM, false);
        params.getInfoFC()->setModeANT(ModeANT::CALIBRATION, false);
        params.getInfoFC()->setModeANT(ModeANT::AUTOTRACKING, false);

        int currentMode = jv.toInt();
        ModeANT mode = ModeANT::MANUAL;

        if(currentMode == 0 || currentMode == 4)
            mode = ModeANT::MANUAL;
        if(currentMode == 1)
        {
            if(obj.value("progmode").toBool())
            {
                mode = ModeANT::TD;
                params.getInfoFC()->setModeANT(mode, true);
            }
            mode = ModeANT::PROGRAMM;
        }
        if(currentMode == 3 && isCalibrationMode)
            mode = ModeANT::CALIBRATION;
        if(currentMode == 3 && !isCalibrationMode)
            mode = ModeANT::AUTOTRACKING;

        params.getInfoFC()->setModeANT(mode, true);

        if(params.getIsCorrection())
            params.getInfoFC()->setModeANT(ModeANT::CORRECTION, true);
    }

    /// поправка по углу места
    jv = obj.value("correction_elevation");
    if(!jv.isUndefined())
        params.getInfoFC()->getRefInfoControl()->setCorrectionElevation(jv.toDouble());

    /// уровень ПТН
    jv = obj.value("signal");
    if(!jv.isUndefined())
        params.setLevelPTN(jv.toDouble());

    /// наличие ЦУ
    jv = obj.value("progmode");
    if(!jv.isUndefined()) {
        params.setIsAntennaTD(jv.toBool());
        params.getInfoFC()->setModeANT(ModeANT::TD, jv.toBool());
    }

    /// измерения углов
    jv = obj.value("measurementsOn");
    bool measurementsOn{false};
    if(!jv.isUndefined())
    {
        measurementsOn = jv.toBool();
        params.getInfoFC()->setModeORM(ModeORM::CHANGE_ANGLE, measurementsOn);
    }

    /// номер измерения
    jv = obj.value("measurementCounter");
    int number{-1};
    if(!jv.isUndefined())
        number = jv.toInt();

    params.getInfoFC()->getRefInfoControl()->setCounterAngle(number);

    if(measurementsOn)
    {
        /// изм. азимут
        jv = obj.value("measurementAZ");
        double az{0.};
        if(!jv.isUndefined())
            az = jv.toDouble();

        /// изм. угол места
        jv = obj.value("measurementEL");
        double el{0.};
        if(!jv.isUndefined())
            el = jv.toDouble();

        int rate = 1;
        jv = obj.value("measurementsRate");
        if(!jv.isUndefined()) {
            rate = jv.toInt();
            ModeORM mode{ModeORM::SEC_1};
            if(rate == 1 || rate == 10)
                mode = ModeORM::SEC_10;
            else if(rate == 2 || rate == 20)
                mode = ModeORM::SEC_20;
            params.getInfoFC()->setModeORM(mode, true);
        }

        if(number != _currentNumber && number > 0)
        {
            _currentNumber = number;

            if(_timeStart == QDateTime::fromSecsSinceEpoch(0))
                _timeStart = QDateTime::fromSecsSinceEpoch(params.getInfoFC()->getRefInfoControl()->getCurrentTime());

            daq::Degree daz, del;
            daz.fromDouble(az);
            del.fromDouble(el);

            QString message = QString("%1: АЗ:%2 УМ:%3").arg(number).arg(daz.toString()).arg(del.toString());
            _journal->writeEvent(message);

            Chunk chaunk;
            chaunk.az = az;
            chaunk.el = el;
            chaunk.t = QDateTime::fromSecsSinceEpoch(_timeStart.toSecsSinceEpoch() + number * rate);
            _vectorAngles.append(chaunk);
        }
    }
    else
    {
        _timeStop = QDateTime::fromSecsSinceEpoch(params.getInfoFC()->getRefInfoControl()->getCurrentTime());
        writeParamsAngles();
        _timeStart = QDateTime::fromSecsSinceEpoch(0);
    }
}

void ParserAntenna::writeParamsAngles()
{
    if(_vectorAngles.isEmpty())
        return;

    QString header = genHeader(params.getNumberKA()), data;

    QString fileName = QString("%1").arg(params.getNumberKA()) + SEPARATOR
            + _timeStart.date().toString("yyyyMMdd")
            + _timeStart.time().toString("hhmm") + SEPARATOR
            + _timeStop.date().toString("yyyyMMdd")
            + _timeStop.time().toString("hhmm")+ EXPANSION_LMF;

    data += header;

    auto nip = params.getNumberNIP();
    for(int i = 0; i < _vectorAngles.size(); ++i)
        data += _vectorAngles[i].toString(nip);

    FileWorkerORM worker(TypeFileORM::ANGLES);
    worker.setNameFile(fileName);
    if(worker.write(data.toUtf8()))
        qDebug() << "success record RCO LMF";

    flushBinaryFile(data.toUtf8());
    _vectorAngles.clear();
}

QString ParserAntenna::genHeader(const int16_t ka)
{
    QString s = "FILE_HEADER\r\n";
    s += "FILE_TYPE:= LMF\r\n";
    s += "FILE_FORMAT:= E3GS.ICD.0001.MMT_3.0\r\n";
    s += "GEN_DATE:= " + _timeStop.date().toString("yyyy/MM/dd") + " " + _timeStop.time().toString("hh:mm:ss")+"\r\n";
    s += "GEN_APP_NAME:= DAQ Server SOFTWARE SKL\r\n";
    s += "GEN_APP_RLS:= 1.0\r\n";
    s += "END_FILE_HEADER\r\n";
    s += "******************************************************************\r\n";
    s += QString("SAT_ID:= %1").arg(ka) + "\r\n";
    s += "******************************************************************\r\n";
    s += "** Measurement data\r\n";

    return s;
}

void ParserAntenna::flushBinaryFile(QByteArray ba)
{
    for(int i = 0; i < 11; i++)
        ba = ba.right(ba.size() - ba.indexOf('\n') - 1);

    QByteArray res;
    while(!QRegExp("\\s*").exactMatch(ba))
    {
        QByteArray lineb = ba.left(ba.indexOf('\n'));
        ba = ba.right(ba.size() - ba.indexOf('\n') - 1);
        QStringList r = QString::fromUtf8(lineb).split(' ', QString::SkipEmptyParts);

        if(r.size() < 6)
            break;

        QTime qtime = QTime::fromString(r[2], "hh:mm:ss.zzz");
        quint32 time = qRound(qtime.msecsSinceStartOfDay() * 1.024); // потому что переводим миллисекунды в 1/2^10
        bool um = false;

        if(r[3] == "EL")
            um = true;
        else if(r[3] == "AZ")
            um = false;
        else
            break;

        quint32 izm = fromValue(r[r.size() - 2].toDouble());
        // время
        quint8 byte0 = time >> 0;
        quint8 byte1 = time >> 8;
        quint8 byte2 = time >> 16;
        quint8 byte3 = time >> 24;

        //измерение
        quint8 byte4 = izm >> 0;
        quint8 byte5 = izm >> 8;
        quint8 byte6 = izm >> 16;
        quint8 byte7 = izm >> 24;
        //тип измерений + резерв
        quint8 byte8 = 0b01100000 | (um << 4);
        //htpthd
        quint8 byte9 = 0b00000000;

        res.append(byte0);
        res.append(byte1);
        res.append(byte2);
        res.append(byte3);
        res.append(byte4);
        res.append(byte5);
        res.append(byte6);
        res.append(byte7);
        res.append(byte8);
        res.append(byte9);
    }

    QString kaString = QString("%1").arg(params.getNumberKA(), 4, 10, QChar('0'));
    QString vitkaString = QString("%1").arg(params.getNumberVitok(), 5, 10, QChar('0'));
    QString seansaString = QString("%1").arg(params.getNumberSeans(), 2, 10, QChar('0'));

    QString fileName = kaString + SEPARATOR + vitkaString + SEPARATOR + seansaString + EXPANSION_UG;

    FileWorkerORM worker(TypeFileORM::ANGLES);
    worker.setNameFile(fileName);
    if(worker.write(res))
        qDebug() << "success record RCO ug";
}

QString ParserAntenna::Chunk::toString(int kis)
{
    QString s;

    s += "MEAS:= " + t.date().toString("yyyy/MM/dd") + " " + t.time().toString("hh:mm:ss.zzz")
            + QString(" AZ %1").arg(kis) + " " + QString::number(az, 'f', 3) + " ZZ\r\n";

    s += "MEAS:= " + t.date().toString("yyyy/MM/dd") + " " + t.time().toString("hh:mm:ss.zzz")
            + QString(" EL %1").arg(kis) + " " + QString::number(el, 'f', 3) + " ZZ\r\n";

    return s;
}
