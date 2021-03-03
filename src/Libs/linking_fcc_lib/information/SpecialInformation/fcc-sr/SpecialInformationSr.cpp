#include "linkingFcc/infornation/SpecialInformation/fcc-sr/SpecialInformationSr.h"

SpecialInformationSr::SpecialInformationSr(const uint16_t id)
    : _id(id)
{
}

void SpecialInformationSr::setConvertPhrase(const QByteArray &phrases)
{
    _phrases = phrases;
    _length = _phrases.size() * 2;
}

QByteArray SpecialInformationSr::serialize()
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out.setByteOrder(QDataStream::LittleEndian);

    out << _length;
    out << PHRASE_LENGTH;
    out << _id;
    array.append(_phrases);

    return array;
}

void SpecialInformationSr::unserialize(QByteArray &array)
{
    if(array.size() < MIN_SIZE_SPECIAL_INFORMATION)
        return;

    QDataStream in(&array, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_10);
    in.setByteOrder(QDataStream::LittleEndian);

    in >> _length;
    auto arrayPhrase = array.right(array.size() - MIN_SIZE_SPECIAL_INFORMATION);
    /// если длина массива слов не совпадает с полученной длиной фразы
    if(arrayPhrase.size() != _length * 2)
    {
        _length = 0;
        return;
    }

    in >> _length;
    in >> _id;
    /// выбор массива слов;
    _phrases = arrayPhrase.toBase64();
}

uint16_t SpecialInformationSr::id() const
{
    return _id;
}

void SpecialInformationSr::setId(const uint16_t &id)
{
    _id = id;
}

