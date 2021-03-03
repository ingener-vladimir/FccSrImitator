#ifndef SPECIALINFORMATION_H
#define SPECIALINFORMATION_H

/*!
    \file
    \brief Класс для работы со специальной информацией
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <stdint.h>
#include <QVector>
#include <QDataStream>

class SpecialInformation
{
    uint16_t _length{0};        ///< Длина информационной части массива СИ в 16р. словах (Word)
    uint16_t _phraseLength{0};  ///< Длина фразы = 32 (Word) (=2,4,32)
    uint16_t _idSI{0};          ///< Идентификатор СИ *
    QString _convertPhrase{""}; ///< Конвертированная в QString::Base64 фраза

    static const uint8_t MIN_SIZE = 6;

public:
    SpecialInformation() {}
    /*!
     * \brief Распаковка массива данных СИ
     * \param array Массив данных
     */
    bool unserializeSpecialInformation(QByteArray& array);
    /*!
     * \brief Получить фразу из СИ в кодировке Base64
     * \return Фраза
     */
    QString getConvertPhrase();

    uint16_t length() const;
    void setLength(const uint16_t &length);

    uint16_t phraseLength() const;
    void setPhraseLength(const uint16_t &phraseLength);

    uint16_t idSI() const;
    void setIdSI(const uint16_t &idSI);

    void resetSI();
};

#endif // SPECIALINFORMATION_H
