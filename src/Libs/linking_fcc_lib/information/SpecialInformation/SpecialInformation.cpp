#include "linkingFcc/infornation/SpecialInformation/SpecialInformation.h"

bool SpecialInformation::unserializeSpecialInformation(QByteArray &array)
{
    if(array.size() < MIN_SIZE)
        return false;

    QDataStream in(&array, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_10);
    in.setByteOrder(QDataStream::LittleEndian);

    in >> _length;
    auto arrayPhrase = array.right(array.size() - MIN_SIZE);
    /// если длина массива слов не совпадает с полученной длиной фразы
    if(arrayPhrase.size() != _length * 2)
    {
        _length = 0;
        return false;
    }

    in >> _phraseLength;
    in >> _idSI;
    /// выбор массива слов;
    _convertPhrase = arrayPhrase.toBase64();

    return true;
}

QString SpecialInformation::getConvertPhrase()
{
    return _convertPhrase;
}

uint16_t SpecialInformation::phraseLength() const
{
    return _phraseLength;
}

void SpecialInformation::setPhraseLength(const uint16_t &phraseLength)
{
    _phraseLength = phraseLength;
}

uint16_t SpecialInformation::idSI() const
{
    return _idSI;
}

void SpecialInformation::setIdSI(const uint16_t &idSI)
{
    _idSI = idSI;
}

uint16_t SpecialInformation::length() const
{
    return _length;
}

void SpecialInformation::setLength(const uint16_t &length)
{
    _length = length;
}

void SpecialInformation::resetSI()
{
    setLength(0);
    setPhraseLength(0);
    setIdSI(0);
    _convertPhrase = "";
}
