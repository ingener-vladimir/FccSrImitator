#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/FactoryFormularFCC.h"

QList<QSharedPointer<IPackage> > FactoryFormularFCC::takeListPackage()
{
    QMutexLocker lock(&_mutex);
    QList<QSharedPointer<IPackage>> pack(_list_pack);
    _list_pack.clear();
    return pack;
}

void FactoryFormularFCC::addTicket(Header &header)
{
    QMutexLocker lock(&_mutex);
    _lastHeader = header;
    _list_pack.append(QSharedPointer<IPackage>(new PackageTicket(header, getMessageNumber())));
}

void FactoryFormularFCC::addPackageDirective152(const TmiFormat format,
                                                const QByteArray &array)
{
    QByteArray data(_lastHeader.serialize());
    data.append(array);
    QMutexLocker lock(&_mutex);
    if(array.size() == 519)
            _list_pack.append(QSharedPointer<IPackage>(new PackageDirective152Old(getMessageNumber(), data)));
        if(array.size() == 520)
            _list_pack.append(QSharedPointer<IPackage>(new PackageDirective152New(getMessageNumber(), data)));

        /*switch (format)
        {
        case TmiFormat::NEW_TMI_FORMAT:
            _list_pack.append(QSharedPointer<IPackage>(new PackageDirective152Old(getMessageNumber(), data)));
            break;
        case TmiFormat::OLD_TMI_FORMAT:
            _list_pack.append(QSharedPointer<IPackage>(new PackageDirective152Old(getMessageNumber(), data)));
            break;
        }*/

}

void FactoryFormularFCC::addPackageDirective112(Header &header,
                                                uint16_t data,
                                                uint32_t time)
{
    QByteArray array;

    switch(header.getHeader().NFORM)
    {

    case TypeInfo::INFO_777 :
    {
        foreach(auto& var, readDZYbyType(TypeFileORM::DISTANCE, data, time))
        {
            array.append(var);
            QMutexLocker lock(&_mutex);
            _list_pack.append(QSharedPointer<IPackage>(new PackageDirective112Distance(getMessageNumber(),
                                                                                       header,
                                                                                       array)));
        }
        break;
    }

    case TypeInfo::INFO_902 :
    {
        foreach(auto& var, readDZYbyType(TypeFileORM::ANGLES, data, time))
        {
            array.append(var);
            QMutexLocker lock(&_mutex);
            _list_pack.append(QSharedPointer<IPackage>(new PackageDirective112Angle(getMessageNumber(),
                                                                                    header,
                                                                                    array)));
        }
        break;
    }

    default:
        break;
    }
}

void FactoryFormularFCC::addPackageDirective198(Header &header, QString name)
{
    QByteArray array;
    array.append(readFile(name));

    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageDirective198(getMessageNumber(),
                                                                       header,
                                                                       array)));
}

void FactoryFormularFCC::addPackageDirective150(QString message)
{
    Q_UNUSED(message)

    QMutexLocker lock(&_mutex);
    _list_pack.append(QSharedPointer<IPackage>(new PackageDirective150()));
}

void FactoryFormularFCC::addPackageDirective155(QByteArray& array)
{
    QMutexLocker lock(&_mutex);
    QByteArray data(_lastHeader.serialize());
    data.append(array);
    _list_pack.append(QSharedPointer<IPackage>(new PackageDirective155(getMessageNumber(), data)));
}

QVector<QByteArray> FactoryFormularFCC::readDZYbyType(TypeFileORM type,
                                                      const uint16_t data,
                                                      const uint32_t time)
{
    Q_UNUSED(data)
    Q_UNUSED(time)

    QVector<QByteArray> vectorArray;
    ParamsCMS& params = ParamsSingleton::getInstance();

    FileWorkerORM worker(type);
    auto path = worker.absolutePathDir();

    QDir workDir(path);

    QStringList nameFilter{"*.ug"};
    if(type == TypeFileORM::DISTANCE)
    {
        nameFilter.clear();
        nameFilter << "*.r0";
    }
    QFileInfoList list = workDir.entryInfoList(nameFilter, QDir::Files ); // сказываем что нас интересуют только файлы

    QFileInfo fileinfo; // сюда будем считывать элементы
    foreach (fileinfo, list) // foreach - приятный подарок-макрос от Qt =)
    {
        auto name = fileinfo.fileName();
        auto syfffix = fileinfo.completeSuffix();
        auto baseName = fileinfo.baseName();
        auto listParam = baseName.split(SEPARATOR);
        if(listParam.size() != NAME_FILE_SIZE || syfffix.size() > 3)
            continue;

        int ka = listParam.at(0).toInt();
        int vitok = listParam.at(1).toInt();
        int seans = listParam.at(2).toInt();

        if(ka == params.getNumberKA()
                && vitok == params.getNumberVitok()
                && seans == params.getNumberSeans())
        {
            worker.setNameFile(name);
            QByteArray array;
            array = worker.read();

            for(int i = 0; i < array.size(); i += CHUNK_SIZE)
                vectorArray.append(array.mid(i, CHUNK_SIZE));
        }
    }

    if(vectorArray.isEmpty())
        vectorArray.append(QByteArray());

    return vectorArray;
}

QByteArray FactoryFormularFCC::readFile(QString name)
{
    Q_UNUSED(name)
    QByteArray array;

    return array;
}

void FactoryFormularFCC::setLastHeader(const Header &lastHeader)
{
    _lastHeader = lastHeader;
}


void FactoryFormularFCC::setLastKA(const int16_t &lastKA)
{
    _lastHeader.getHeader().NKA = lastKA;
}

void FactoryFormularFCC::setSeansPrm(uint16_t nSeansa, uint16_t nVitka) {
    _lastHeader.getHeader().NSEANS = nSeansa;
    _lastHeader.getHeader().NVITKA = nVitka;
}

void FactoryFormularFCC::setNipNumber(int16_t nip) {
    _lastHeader.getHeader().NNIP_KTC = nip;
}

void FactoryFormularFCC::setCode(const CodeTicket code)
{
    _lastHeader.getHeader().Code = code;
}

Header& FactoryFormularFCC::getLastHeader()
{
    return _lastHeader;
}

uint32_t FactoryFormularFCC::getMessageNumber()
{
    return (_msg_num == 0) ? _msg_num = 1 : _msg_num++;
}


TypeFactory FactoryFormularFCC::getTypeFactoryFormular()
{
    return TypeFactory::FCC;
}
