#ifndef BITUTILS_H
#define BITUTILS_H

#include <stdint.h>

class BitUtils final
{
    BitUtils() {}
public:
    /*!
     * @brief Шаблонная функция получения бита по индексу
     * @param value Переменная, из которой брать
     * @param index Индекс бита для установки
     * @return Флаг состояния
     */
    template<class T>
    static bool getValueByBitInbex(const T& value, const uint8_t index = 0)
    {
        return (value >> (uint8_t)index) & 1u;
    }

    /*!
     * @brief Шаблонная функция записи бита по индексу
     * @param value Переменная, в которую необходимо записать
     * @param index Индекс бита для установки
     * @param state Состояние
     */
    template<class T>
    static void setValueByBitInbex(T& value, const uint8_t index, const bool state)
    {
        if(state)
            value |= (1 << index);
        else
            value &= ~(1 << index);
    }
};

#endif // BITUTILS_H
