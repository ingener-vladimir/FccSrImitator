#ifndef BASEFUNCTIONCONTROL_H
#define BASEFUNCTIONCONTROL_H

#include <stdint.h>
#include <QByteArray>

#include "StructFunctionControl.h"

struct OldParamsCMS
{
    bool MODE_WORK{false};
    bool MODE_IMIT_IF{false};
    bool MODE_IMIT_HF{false};
    bool MODE_PREPARE{false};
    bool RADIATION_AMPLIFIER_1{false};
    bool RADIATION_AMPLIFIER_2{false};
    bool MODULATION_PNS{false};
    bool CONVERTER_UP{false};
    bool MSHY{false};
    bool POLAR_UP{false};
    bool LIU{false};
    bool CONVERTER_UP_COMPLECT_1{false};
    bool CONVERTER_DOWN_COMPLECT_2{false};
    bool CONVERTER_DOWN_COMPLECT_1{false};
    bool NP_2{false};
    bool NP_1{false};
    bool NP{false};
    bool AYY495_COMPLECT_1{false};
    bool AYY495_COMPLECT_2{false};
    bool TEST_TRANSLATION{false};
    bool MANUAL{false};
    bool PROGRAMM{false};
    bool CORRECTION{false};
    bool TD{false};
    bool CALIBRATION{false};
    bool CHANGE_DISTANCE{false};
    bool CHANGE_ANGLE{false};
    bool ID_ORM{false};
    bool ANT{false};
    bool SCU1{false};
    bool SCU2{false};
};

class BaseFunctionControl
{
    StructFunctionControl* _infoControl{nullptr};
    QMutex _mutex;

public:
    BaseFunctionControl(StructFunctionControl* infoControl);
    virtual ~BaseFunctionControl() = default;

    BaseFunctionControl& operator=(BaseFunctionControl& control);
    BaseFunctionControl(BaseFunctionControl &control);

    ///< Состояние системы (Word) , наличие режима -1 в соответствующем разряде
    virtual bool getSystemState(const SystemState) { return false; }
    virtual void setSystemState(const SystemState, const bool) {}

    // Комплекты (Word) , 0 - 1-ый комплект, 1 - 2-ой комплект
    virtual uint8_t getComplects(const Complects) { return false; }
    virtual void setComplects(const Complects, const bool) {}

    ///< Наличие обмена (Word) , обмен с устройством -1 в соответствующем разряде
    virtual bool getSwap(const Swap) { return false; }
    virtual void setSwap(const Swap, const bool) {}

    ///< Режим АНТ (Word) , наличие режима -1 в соответствующем разряде, при программном или ручном режиме указывается наличие типа поправки
    virtual bool getModeANT(const ModeANT) { return false; }
    virtual void setModeANT(const ModeANT, const bool) {}

    // Режим РКО (Word) , режим -1 в соответствующем разряде
    virtual bool getModeORM(const ModeORM) { return false; }
    virtual void setModeORM(const ModeORM , const bool) {}

    /*!
     * \brief Создать массив данных с параметрами для ИФКТ
     * \param[out] array Массив с данными
     */
    virtual void createByteArray(QByteArray& ) {}

    virtual void resetTempMeasurementORM() {}

    virtual void setParamsPreviousCMS(OldParamsCMS&) {}

    StructFunctionControl *getRefInfoControl();

    OldParamsCMS getOldParams();

protected:
    void createBaseByteArray(QByteArray& array);
    void setInfoControl(StructFunctionControl *infoControl);

};

#endif // BASEFUNCTIONCONTROL_H
