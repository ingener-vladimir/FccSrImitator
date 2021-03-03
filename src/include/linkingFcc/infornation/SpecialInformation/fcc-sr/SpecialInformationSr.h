#ifndef SPECIALINFORMATIONSR_H
#define SPECIALINFORMATIONSR_H

#include <stdint.h>
#include <QString>
#include <QDataStream>

class SpecialInformationSr
{
    QByteArray _phrases;        ///< Информация
    uint16_t _length;

    static const uint8_t MIN_SIZE_SPECIAL_INFORMATION = 6;
    static const uint16_t PHRASE_LENGTH = 32; ///< Длина фразы = 32 (Word) (=2,4,32)
    uint16_t _id{1};
public:
    SpecialInformationSr() {}
    SpecialInformationSr(const uint16_t id);

    void setConvertPhrase(const QByteArray &phrases);
    uint16_t id() const;
    void setId(const uint16_t &id);

    QByteArray serialize();
    void unserialize(QByteArray& array);
};

#endif // SPECIALINFORMATIONSR_H
