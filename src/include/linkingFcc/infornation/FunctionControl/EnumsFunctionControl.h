#ifndef ENUMSFUNCTIONCONTROL_H
#define ENUMSFUNCTIONCONTROL_H

/*!
    \file
    \brief Сборник перечислений для ИФКТ
    \author Саньков Владимир
    \version 0.1
    \date октябрь 2019 г.
*/

#include <QHash>
#include <QMultiMap>

/// Состояние КИС
enum class SystemState : uint8_t
{
    LOCK_CARRIER = 0,       ///< Захват несущ.
    LOCK_PNS,               ///< Захват ПШС
    MODE_WORK,              ///< Реж. работа
    MODE_CLOSE,             ///< Закрытый режим
    MODE_IMIT_IF,           ///< Реж. имит. ПЧ
    MODE_IMIT_HF,           ///< Реж. имит. ВЧ
    MODE_PREPARE,           ///< Реж. подготовка
    RADIATION_AMPLIFIER_1,  ///< Изл. УМ 1 кмп
    RADIATION_AMPLIFIER_2,  ///< Изл. УМ 2 кмп
    TRANSMITTER,            ///< ПРД в ант./ нагр.
    MODULATION_PNS,         ///< Вкл. модуляции ПШС
    RESERVE1,
    DOPLER_COMPLECT_ANSWER, ///< Вкл. комп. допл. по отв.
    DOPLER_COMPLECT_TD,     ///< Вкл. комп. допл. по ЦУ
    READY_ES,               ///< Готовность ЗС к упр.
    MODEM_RADIATION,        ///< MOdem radiation
    COMPLECT_MSHU,
    // 649
    LINK,                   ///< Связь
    MODE_SCPI,              ///< Режим СКЗИ Вкл.
    TRAMSMITTER,            ///< ПРД 0-лок. 1-уд.
    READY_PEVM,             ///< Гот.рез ПЭВМ
    READY_CMOS,             ///< Гот. ЦМОС
    MAIN_RESERVE,           ///< Осн./Рез
    ANTENNA,                ///< АНТ 0-лок. 1-уд.
    GROUP,                  ///< Группиров.
    ARCHIVE                 ///< Архив
};

/// Бортовой дешифратор
enum class OnboardDecoder : uint8_t
{
    HS1 = 0, ///< ПК1 РК
    HS2      ///< ПК2 РК
};

/// Комплекты
enum class Complects : uint8_t
{
    MODEM = 0,          ///< Модем Т-Б
    CONVERTER_UP,       ///< Конв. вверх
    AMPLIFIER,          ///< УМ
    MSHY,               ///< МШУ 1
    MSHY2,              ///< МШУ 2
    MSHY3,              ///< МШУ 3
    YAY374,             ///< ЯУ374
    POLAR_RECEIVER = 8, ///< Поляр. ПРМ.АЛ/П
    POLAR_UP = 9,       ///< Поляр. вверх Л/П
    // 649
    NP,                 ///< НП
    TRAMSMITTER,        ///< ПРД
    TRAMSMITTER_ANTENNA,///< ПРД Ант
    TRAMSMITTER_LOAD,   ///< ПРД нагр
    TRAMSMITTER_ERROR,  ///< ПРД Ошибка
    POLAR_DOWN          ///< Поляр.вниз Л/П
};

/// Режим антенны
enum class ModeANT : uint8_t
{
    MANUAL = 0,   ///< Ручн.
    PROGRAMM,     ///< Прог.
    AUTOTRACKING, ///< Автосопр.
    CORRECTION,   ///< Попр.
    TD,           ///< ЦУ
    CALIBRATION,  ///< Калибровка
    // 649
    STEPTRACK,    ///< StepTrack
    FAILURE,      ///< отказ
    ANTENNA,      ///< АНТ
    MONOPULSE,    ///< Monopulse
    POLAR         ///< Поляр. 0-Лев. 1-Прав
};

/// Квитанция разовой команды
enum class TicketOTC : uint8_t
{
    NULL_OTC = 0,    ///< 0 КВ
    PLUS,            ///< + КВ
    PROCESS,         ///< Идет
    MINUS,           ///< - КВ
    SEND_MASK = 5,  /// mask of send
    PROCESS_OOTC = 6, ///< Идет ОРК
    FAULT_COUNTER = 7
};

/// Квитанция специальной ифнормации
enum class TicketSI : uint8_t
{
    NULL_SI = 0, ///< 0 КВ
    MINUS,       ///< - КВ
    PLUS,        ///< + КВ
    PROCESS_SI,  ///< ИД СИ
    STOP_SI,     ///< Ост СИ
    ON_SI,       ///< Вкл СИ
    NULL_ZKV     ///< 0 ЗКВ
};

/// Режим телеметрии
enum class ModeTLM : uint8_t
{
    TLM_1KHZ = 0,   ///< ТЛМ 1 кГц
    TLM_8KHZ,       ///< ТЛМ 8 кГц
    SLIM_STRIP,     ///< Узкая полоса
    AVERAGE_STRIP,  ///< Средн. полоса
    WIDE_STRIP,     ///< Широк. полоса
};

/// Режим РКО
enum class ModeORM : uint8_t
{
    ID_DOPLER = 0,       ///< ИД допл.
    CHANGE_DISTANCE,     ///< Изм. дальн.
    CHANGE_ANGLE,        ///< Изм. угл.
    ID_ORM,              ///< ИД РКО
    SEC_1 = 5,           ///< 1с.
    SEC_10,              ///< 10с.
    SEC_20,              ///< 20с.
    // 649
    CALIBRATION,
    SEC_10_20
};

/// Авария устройств
enum class AlarmDevices : uint8_t
{
    MODEM_COMPLECT_1 = 0,       ///< Модем Т-Б 1 кмп
    MODEM_COMPLECT_2,           ///< Модем Т-Б 2 кмп
    LIU,                        ///< БСУ (СКЗИ)
    CONVERTER_UP_COMPLECT_1,    ///< Конв.вверх 1 кмп
    CONVERTER_UP_COMPLECT_2,    ///< Конв.вверх 2 кмп
    CONVERTER_DOWN_COMPLECT_1,  ///< Конв.вниз 1 кмп
    CONVERTER_DOWN_COMPLECT_2,  ///< Конв.вниз 2 кмп
    NP_1,                       ///< НП1
    NP_2,                       ///< НП2
    AMPLIFIER1,                 ///< УМ1
    AMPLIFIER2,                 ///< УМ2
    YYP,                        ///< УУП
    METEOSTATION,               ///< Метеостанция
    TEST_TRANSLATION,           ///< Тест транс.
    ANT,                        ///< АНТ
    RECEIVER_ANT                ///< ПРМ. АНТ
};

/// Наличие обмена
enum class Swap : uint8_t
{
    MODEM_COMPLECT_1,           ///< Модем Т-Б 1 кмп
    MODEM_COMPLECT_2,           ///< Модем Т-Б 2 кмп
    LIU,                        ///< БСУ (СКЗИ)
    CONVERTER_UP_COMPLECT_1,    ///< Конв.вверх 1 кмп
    CONVERTER_UP_COMPLECT_2,    ///< Конв.вверх 2 кмп
    CONVERTER_DOWN_COMPLECT_1,  ///< Конв.вниз 1 кмп
    CONVERTER_DOWN_COMPLECT_2,  ///< Конв.вниз 2 кмп
    NP,                         ///< НП
    NP_1,                       ///< НП1
    NP_2,                       ///< НП2
    AMPLIFIER1,                 ///< УМ1
    AMPLIFIER2,                 ///< УМ2
    AYY495_COMPLECT_1,          ///< ЯУ495 1 комп
    AYY495_COMPLECT_2,          ///< ЯУ495 2 комп
    YYP,                        ///< УУП
    METEOSTATION,               ///< Метеостанция
    SCU1,                       ///< БУМП1(блок управления переключателем)
    SCU2,                       ///< БУМП2(блок управления переключателем)
    TEST_TRANSLATION,           ///< Тест транс.
    ANT,                        ///< АНТ
    // 649
    TRANSMITTER_1,              ///< ПРД 1
    TRANSMITTER_2,              ///< ПРД 2
    CORTEX                      ///< Cortex
};

/// Положение переключателей
enum class Switches : uint8_t
{
    S1,
    S3,
    S2,
    S4,
    S5,
    S6,
    S7,
    S8,
    TLT
};

static QMultiMap<uint8_t, Swap> SWAP_MAP
{
    {0, Swap::MODEM_COMPLECT_1},
    {1, Swap::MODEM_COMPLECT_2},
    {2, Swap::LIU},
    {3, Swap::CONVERTER_UP_COMPLECT_1},
    {4, Swap::CONVERTER_UP_COMPLECT_2},
    {5, Swap::CONVERTER_DOWN_COMPLECT_1},
    {6, Swap::CONVERTER_DOWN_COMPLECT_2},
    {7, Swap::NP_1},
    {7, Swap::SCU1},
    {8, Swap::NP_2},
    {8, Swap::SCU2},
    {9, Swap::AMPLIFIER1},
    {10, Swap::AMPLIFIER2},
    {11, Swap::YYP},
    {11, Swap::NP},
    {11, Swap::AYY495_COMPLECT_1},
    {12, Swap::METEOSTATION},
    {12, Swap::AYY495_COMPLECT_2},
    {13, Swap::TEST_TRANSLATION},
    {14, Swap::ANT}
};

static QMap<uint8_t, SystemState> SYSTEM_STATE_MAP_649
{
    {0, SystemState::LINK},
    {1, SystemState::RADIATION_AMPLIFIER_1},
    {2, SystemState::MODE_WORK},
    {3, SystemState::MODE_SCPI},
    {4, SystemState::MODE_IMIT_IF},
    {5, SystemState::TRAMSMITTER},
    {6, SystemState::MODE_IMIT_HF},
    {7, SystemState::READY_PEVM},
    {8, SystemState::READY_CMOS},
    {9, SystemState::MAIN_RESERVE},
    {10, SystemState::MODULATION_PNS},
    {11, SystemState::ANTENNA},
    {12, SystemState::GROUP},
    {13, SystemState::MODE_PREPARE},
    {14, SystemState::ARCHIVE},
    {15, SystemState::RADIATION_AMPLIFIER_2}
};

static QMap<uint8_t, SystemState> SYSTEM_STATE_MAP
{
    {0, SystemState::LOCK_CARRIER},
    {1, SystemState::LOCK_PNS},
    {2, SystemState::MODE_WORK},
    {3, SystemState::MODE_CLOSE},
    {4, SystemState::MODE_IMIT_IF},
    {5, SystemState::MODE_IMIT_HF},
    {6, SystemState::MODE_PREPARE},
    {7, SystemState::RADIATION_AMPLIFIER_1},
    {8, SystemState::RADIATION_AMPLIFIER_2},
    {9, SystemState::TRANSMITTER},
    {10, SystemState::MODULATION_PNS},
    {11, SystemState::RESERVE1},
    {12, SystemState::DOPLER_COMPLECT_ANSWER},
    {13, SystemState::DOPLER_COMPLECT_TD},
    {14, SystemState::READY_ES},
    {15, SystemState::MODEM_RADIATION}
};

static QMap<uint8_t, SystemState> SYSTEM_STATE_MAP_330
{
    {0, SystemState::LOCK_CARRIER},
    {1, SystemState::LOCK_PNS},
    {2, SystemState::MODE_WORK},
    {3, SystemState::MODE_CLOSE},
    {4, SystemState::MODE_IMIT_IF},
    {5, SystemState::MODE_IMIT_HF},
    {6, SystemState::MODE_PREPARE},
    {7, SystemState::RADIATION_AMPLIFIER_1},
    {8, SystemState::RADIATION_AMPLIFIER_2},
    {9, SystemState::TRANSMITTER},
    {10, SystemState::MODULATION_PNS},
    {11, SystemState::RESERVE1},
    {12, SystemState::DOPLER_COMPLECT_ANSWER},
    {13, SystemState::DOPLER_COMPLECT_TD},
    {14, SystemState::READY_ES},
    {15, SystemState::MODEM_RADIATION}
};

static QMap<uint8_t, SystemState> SYSTEM_STATE_MAP_344
{

};

static QMap<uint8_t, SystemState> SYSTEM_STATE_MAP_345
{

};

static QMap<uint8_t, SystemState> SYSTEM_STATE_MAP_346
{

};

static QMap<uint8_t, Complects> COMPLECTS_MAP
{
    {0, Complects::MODEM},
    {1, Complects::CONVERTER_UP},
    {2, Complects::AMPLIFIER},
    {3, Complects::MSHY},
    {4, Complects::MSHY2},
    {5, Complects::MSHY3},
    {8, Complects::POLAR_RECEIVER},
    {9, Complects::POLAR_UP}
};

static QMap<uint8_t, Complects> COMPLECTS_MAP_649
{
    {1, Complects::YAY374},
    {3, Complects::CONVERTER_UP},
    {4, Complects::MSHY2},
    {5, Complects::MSHY},
    {7, Complects::NP},
    {9, Complects::TRAMSMITTER},
    {10, Complects::TRAMSMITTER_ANTENNA},
    {11, Complects::TRAMSMITTER_LOAD},
    {12, Complects::TRAMSMITTER_ERROR},
    {14, Complects::POLAR_UP},
    {15, Complects::POLAR_DOWN}
};

static QMap<uint8_t, Complects> COMPLECTS_MAP_330
{
    {0, Complects::MODEM},
    {1, Complects::CONVERTER_UP},
    {2, Complects::AMPLIFIER},
    {3, Complects::MSHY},
    {4, Complects::MSHY2},
    {5, Complects::MSHY3},
    {8, Complects::POLAR_RECEIVER},
    {9, Complects::POLAR_UP}

};

static QMap<uint8_t, Complects> COMPLECTS_MAP_344
{

};

static QMap<uint8_t, Complects> COMPLECTS_MAP_345
{

};

static QMap<uint8_t, Complects> COMPLECTS_MAP_346
{

};

static QMap<uint8_t, Swap> SWAP_MAP_649
{
    {2, Swap::LIU},
    {3, Swap::CONVERTER_UP_COMPLECT_2},
    {4, Swap::CONVERTER_UP_COMPLECT_1},
    {5, Swap::CONVERTER_DOWN_COMPLECT_2},
    {6, Swap::NP_2},
    {7, Swap::NP_1},
    {9, Swap::AYY495_COMPLECT_1},
    {10, Swap::TRANSMITTER_2},
    {11, Swap::TRANSMITTER_1},
    {12, Swap::CONVERTER_DOWN_COMPLECT_1},
    {13, Swap::AYY495_COMPLECT_2},
    {14, Swap::TEST_TRANSLATION},
    {15, Swap::CORTEX}
};

static QMap<uint8_t, Swap> SWAP_MAP_330
{
    {0, Swap::MODEM_COMPLECT_1},
    {1, Swap::MODEM_COMPLECT_2},
    {2, Swap::LIU},
    {3, Swap::CONVERTER_UP_COMPLECT_1},
    {4, Swap::CONVERTER_UP_COMPLECT_2},
    {5, Swap::CONVERTER_DOWN_COMPLECT_1},
    {6, Swap::CONVERTER_DOWN_COMPLECT_2},
    {7, Swap::NP_1},
    {7, Swap::SCU1},
    {8, Swap::NP_2},
    {8, Swap::SCU2},
    {9, Swap::AMPLIFIER1},
    {10, Swap::AMPLIFIER2},
    {11, Swap::YYP},
    {11, Swap::NP},
    {11, Swap::AYY495_COMPLECT_1},
    {12, Swap::METEOSTATION},
    {12, Swap::AYY495_COMPLECT_2},
    {13, Swap::TEST_TRANSLATION},
    {14, Swap::ANT}

};

static QMap<uint8_t, Swap> SWAP_MAP_344
{

};

static QMap<uint8_t, Swap> SWAP_MAP_345
{

};

static QMap<uint8_t, Swap> SWAP_MAP_346
{

};

static QMultiMap<uint8_t, ModeANT> MODE_ANT_MAP_649
{
    {0, ModeANT::MANUAL},
    {1, ModeANT::PROGRAMM},
    {2, ModeANT::STEPTRACK},
    {2, ModeANT::MONOPULSE},
    {3, ModeANT::CALIBRATION},
    {7, ModeANT::CORRECTION},
    {8, ModeANT::TD},
    {9, ModeANT::FAILURE},
    {11, ModeANT::ANTENNA},
    {12, ModeANT::POLAR}
};

static QMap<uint8_t, ModeANT> MODE_ANT_MAP
{
    {0, ModeANT::MANUAL},
    {1, ModeANT::PROGRAMM},
    {2, ModeANT::AUTOTRACKING},
    {3, ModeANT::CORRECTION},
    {4, ModeANT::TD},
    {5, ModeANT::CALIBRATION}
};

static QMap<uint8_t, ModeANT> MODE_ANT_MAP_330
{
    {0, ModeANT::MANUAL},
    {1, ModeANT::PROGRAMM},
    {2, ModeANT::AUTOTRACKING},
    {3, ModeANT::CORRECTION},
    {4, ModeANT::TD},
    {5, ModeANT::CALIBRATION}

};

static QMap<uint8_t, ModeANT> MODE_ANT_MAP_344
{

};

static QMap<uint8_t, ModeANT> MODE_ANT_MAP_345
{

};

static QMap<uint8_t, ModeANT> MODE_ANT_MAP_346
{

};

static QMap<uint8_t, ModeORM> MODE_ORM_MAP_649
{
    {1, ModeORM::CHANGE_DISTANCE},
    {2, ModeORM::CHANGE_ANGLE},
    {3, ModeORM::ID_ORM},
    {5, ModeORM::SEC_10_20},
    {6, ModeORM::CALIBRATION},
};

static QMap<uint8_t, ModeORM> MODE_ORM_MAP
{
    {0, ModeORM::ID_DOPLER},
    {1, ModeORM::CHANGE_DISTANCE},
    {2, ModeORM::CHANGE_ANGLE},
    {3, ModeORM::ID_ORM},
    {5, ModeORM::SEC_1},
    {6, ModeORM::SEC_10},
    {7, ModeORM::SEC_20}
};

static QMap<uint8_t, ModeORM> MODE_ORM_MAP_330
{
    {0, ModeORM::ID_DOPLER},
    {1, ModeORM::CHANGE_DISTANCE},
    {2, ModeORM::CHANGE_ANGLE},
    {3, ModeORM::ID_ORM},
    {5, ModeORM::SEC_1},
    {6, ModeORM::SEC_10},
    {7, ModeORM::SEC_20}

};

static QMap<uint8_t, ModeORM> MODE_ORM_MAP_344
{

};

static QMap<uint8_t, ModeORM> MODE_ORM_MAP_345
{

};

static QMap<uint8_t, ModeORM> MODE_ORM_MAP_346
{

};

static QHash<uint8_t, QString> HASH_COMPLECTS
{
    {(uint8_t)Complects::MODEM, QString("Модем")},
    {(uint8_t)Complects::CONVERTER_UP, QString("Конвертер вверх")},
    {(uint8_t)Complects::AMPLIFIER, QString("Усилитель мощности")},
    {(uint8_t)Complects::MSHY, QString("МШУ")},
    {(uint8_t)Complects::YAY374, QString("ЯУ374")},
    {(uint8_t)Complects::MSHY2, QString("МШУ 2")},
    {(uint8_t)Complects::NP, QString("Навигационный приемник")},
    {(uint8_t)Complects::TRAMSMITTER_ANTENNA, QString("Антенна")},

};

#endif // ENUMSFUNCTIONCONTROL_H

