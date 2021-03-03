#include "linkingFcc/infornation/ParamsController/BaseParamsController.h"

BaseParamsController::BaseParamsController()
{

}

BaseParamsController::~BaseParamsController()
{

}

void BaseParamsController::setCorrectMode(const bool modeWork,
                                          const bool modePrepare,
                                          const bool modeImitIF,
                                          const bool modeImitHF)
{
    params.getInfoFC()->setSystemState(SystemState::MODE_WORK, modeWork);
    params.getInfoFC()->setSystemState(SystemState::MODE_PREPARE, modePrepare);
    params.getInfoFC()->setSystemState(SystemState::MODE_IMIT_IF, modeImitIF);
    params.getInfoFC()->setSystemState(SystemState::MODE_IMIT_HF, modeImitHF);
}

void BaseParamsController::setJournal(QSharedPointer<IJournal> journal)
{
    _journal = journal;
}
