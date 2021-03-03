#ifndef PERIODICITY_H
#define PERIODICITY_H

#include <stdint.h>

enum class Periodicity : uint8_t
{
    ONCE = 0,    // разовая команда
    CYCLICAL = 1 // цикличсекая команда
};

#endif // PERIODICITY_H
