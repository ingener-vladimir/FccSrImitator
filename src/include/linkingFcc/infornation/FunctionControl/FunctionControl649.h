#ifndef FUNCTIONCONTROL649_H
#define FUNCTIONCONTROL649_H

#include "BaseFunctionControl.h"

class FunctionControl649 : public BaseFunctionControl
{
public:
    FunctionControl649(StructFunctionControl* control);
    ~FunctionControl649() {}

    ///< Состояние системы (Word) , наличие режима -1 в соответствующем разряде
    bool getSystemState(const SystemState index) override;
    void setSystemState(const SystemState mode, const bool state) override;

    // Комплекты (Word) , 0 - 1-ый комплект, 1 - 2-ой комплект
    uint8_t getComplects(const Complects index) override;
    void setComplects(const Complects complect, const bool state) override;

    ///< Наличие обмена (Word) , обмен с устройством -1 в соответствующем разряде
    bool getSwap(const Swap index) override;
    void setSwap(const Swap numSwap, const bool state) override;

    ///< Режим АНТ (Word) , наличие режима -1 в соответствующем разряде, при программном или ручном режиме указывается наличие типа поправки
    bool getModeANT(const ModeANT mode) override;
    void setModeANT(const ModeANT mode, const bool state) override;

    // Режим РКО (Word) , режим -1 в соответствующем разряде
    virtual bool getModeORM(const ModeORM mode) override;
    virtual void setModeORM(const ModeORM mode, const bool state) override;

    /*!
     * \brief Создать массив данных с параметрами для ИФКТ
     * \param[out] array Массив с данными
     */
    void createByteArray(QByteArray& array) override;

    void resetTempMeasurementORM() override;

    void setParamsPreviousCMS(OldParamsCMS& strct) override;
};

#endif // FUNCTIONCONTROL649_H