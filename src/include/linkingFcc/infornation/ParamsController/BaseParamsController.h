#ifndef BASEPARAMSCONTROLLER_H
#define BASEPARAMSCONTROLLER_H

#include "interface/linkingFcc/IParamsController.h"

class BaseParamsController : public IParamsController
{

public:
    BaseParamsController();
    ~BaseParamsController();
    /*!
     * \brief Установить новые параметры
     */
    void setNewParams() override {}
    void setJournal(QSharedPointer<IJournal> journal) override;

protected:
    ParamsCMS& params = ParamsSingleton::getInstance();
    QSharedPointer<IJournal> _journal{nullptr};
    /*!
     * \brief Установить текущий режим работы станции
     * \param params Текущие параметры
     * \param modeWork Флаг режима "Работы"
     * \param modePrepare Флаг режима "Подготовка"
     * \param modeImitIF Флаг режима "Имит. ПЧ"
     * \param modeImitHF Флаг режима "Имит. ВЧ"
     */
    void setCorrectMode(const bool modeWork = false,
                        const bool modePrepare = false,
                        const bool modeImitIF = false,
                        const bool modeImitHF = false);
};

#endif // BASEPARAMSCONTROLLER_H
