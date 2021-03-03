#ifndef TMIFORMAT_H
#define TMIFORMAT_H

enum class TmiFormat
{
    OLD_TMI_FORMAT, ///< пакет под номером 8.1 в протоколе "Старый формат" ТМИ кадра"
    NEW_TMI_FORMAT, ///< пакет под номером 8.2 в протоколе "Новый формат" ТМИ кадра"
};

#endif // TMIFORMAT_H
