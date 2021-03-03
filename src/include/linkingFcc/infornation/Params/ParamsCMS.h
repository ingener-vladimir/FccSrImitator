#ifndef PARAMSCMS_H
#define PARAMSCMS_H

/*!
    \file
    \brief Класс, хранящий все имеющиеся параметры КИС
    \author Саньков Владимир
    \version 0.1
    \date октябрь 2019 г.
*/

#include <QString>
#include <stdint.h>
#include <QMutexLocker>
#include <QMap>

#include "linkingFcc/infornation/FunctionControl/InfoFunctionControl.h"
#include "linkingFcc/infornation/CommandControl/CommandControl.h"
#include "linkingFcc/infornation/SpecialInformation/SpecialInformation.h"
#include "linkingFcc/infornation/SingleCommand/SingleCommand.h"
#include "linkingFcc/infornation/SpecialCommandControl/SpecialCC.h"
#include "linkingFcc/infornation/FunctionControl/StructFunctionControl.h"
#include "linkingFcc/Singleton/Singleton.h"

#define _NAME_OF_ARG(ARG) #ARG

class ParamsCMS
{
    // состояние КИС
    bool isConnectedFCC{false};           ///< соединение с ЦУПом
    int16_t numberKA{0};                 ///< КА
    int16_t numberSeans{0};               ///< № сеанса
    int16_t numberVitok{0};               ///< № витка
    int16_t numberNIP{512};
    bool control{false};                  ///< получить управление(отдать управление)
    bool controlCRT{false};

    // АС
    double azimuthProgramm{1.};           ///< азимут программный
    double elevProgramm{1.};              ///< угол места программный
    bool isCorrection{false};             ///< наличие поправки
    double levelPTN{0.};                  ///< уровень ПТН
    bool isAntennaTD{false};              ///< наличие ЦУ в антенне
    bool isModemTD{false};                ///< наличие ЦУ в модеме
    bool isCalibrationMode{false};

    // компенсация доплера
    bool idCU{false};                     ///< ИД(Есть ЦУ)
    bool lockAnswer{false};               ///< ИД(Захват)
    uint64_t doplerTimeTD{0};
    double compensationCarrierTD{0.};     ///< компенсация несущей
    double compensationPNSTD{0.};         ///< компенсация ПШС
    uint64_t doplerTimeAnswer{0};
    double compensationCarrierAnswer{0.}; ///< компенсация несущей
    double compensationPNSAnswer{0.};     ///< компенсация ПШС

    StructFunctionControl* _functionControl{nullptr};
    QSharedPointer<BaseFunctionControl> infoFC;           ///< функциональный контроль
    QSharedPointer<BaseCommandControl> commands;         ///< команды управления
    SpecialInformation specialInfo;       ///< специальная информация
    SingleCommand singleCommand;          ///< разовая команда
    SpecialCC specialCC;                  ///< пользовательские КУ

    mutable QMutex _mutex;

    QHash<uint8_t, bool> stateComplects{};
    bool _isModemCortex{false};

    bool _isSendingSingleCmd{false};
    bool _isSendingSpecialSingleCmd{false};

    double _dopplerPNCorrection{0.};

    int16_t _complectMSHU{0};

    int _realCMDNum{0};

    static const uint16_t COOL_APPARAT = 649;

public:
    ParamsCMS();
    ~ParamsCMS();

    /*!
     *   \brief сериализация параметров устроства в формат json
     *   \return json объект
     */
    QJsonObject serializeToJSON();

    /*!
     *   \brief распаковка параметров устройства во внутренный формат из json.
     *   \param[in] json документ
     *   \return результат распаковки
     */
    bool unserializeFromJSON(const QJsonDocument &) { return true; }

    // состояние КИС
    void setParamsSession(const int16_t KA, const int16_t seans, const int16_t vitok);
    void setDefaultParams();

    bool getIsConnectedFCC() const;
    void setIsConnectedFCC(bool value);
    QString getIsConnectedFCCFieldName() { return _NAME_OF_ARG(isConnectedFCC); }

    QString getIsSendingSpecialSingleCmdFieldName() { return  _NAME_OF_ARG(isSendingSpecialSingleCmd); }
    bool getIsSendingSpecialSingleCmd() const;
    void setIsSendingSpecialSingleCmd(bool value);

    QString getIsSendingSingleCmdFieldName() { return  _NAME_OF_ARG(isSendingSingleCmd); }
    bool getIsSendingSingleCmd() const;
    void setIsSendingSingleCmd(bool value);

    int16_t getNumberKA() const;
    void setNumberKA(const int16_t KA);
    void setNumberKA();
    QString getNumberKAFieldName() { return _NAME_OF_ARG(numberKA); }

    int16_t getNumberSeans() const;
    void setNumberSeans(const int16_t &value);
    QString getNumberSeansFieldName() { return _NAME_OF_ARG(numberSeans); }

    int16_t getNumberVitok() const;
    void setNumberVitok(const int16_t &value);
    QString getNumberVitokFieldName() { return _NAME_OF_ARG(numberVitok); }

    int16_t getMSHUComplect() const;
    void setMSHUComplect(const int16_t &value);
    QString getMSHUComplectFieldName() { return _NAME_OF_ARG(complectMSHU); }

    double getDopplerPNCorrection() const;
    void setDopplerPNCorrection(const double &value);
    QString getDopplerPNCorrectionFieldName() { return _NAME_OF_ARG(dopplerPNCorrection); }

    int16_t getNumberNIP() const;
    void setNumberNIP(const int16_t &value);

    bool getControl() const;
    void setControl(bool value);

    bool getControlCRT() const;
    void setControlCRT(bool value);

    QString getTimeCMSFieldName() { return QString("timeKIS"); }
    QString getTimeNPFieldName() { return QString("timeNP"); }
    QString getDiscrepancyFieldName() { return QString("discrepancy"); }
    QString getModeWorkPFieldName() { return QString("modeWork"); }
    QString getModePrepareFieldName() { return QString("modePrepare"); }
    QString getModeIFFieldName() { return QString("modePCH"); }
    QString getModeHFFieldName() { return QString("modeVCH"); }
    QString getRadiationElev1FieldName() { return QString("radiationElev1"); }
    QString getRadiationElev2FieldName() { return QString("radiationElev2"); }
    QString getLockCarrierFieldName() { return QString("lockCarrier"); }
    QString getLockPNSFieldName() { return QString("lockPSHS"); }
    QString getRadiationFieldName() { return QString("radiation"); }
    QString getModulationPNSFieldName() { return QString("modulationPNS"); }
    QString getControlFieldName() { return QString("control"); }
    QString getLevelSignalFieldName() { return QString("levelSignal"); }
    QString getDeviationFreqFieldName() { return QString("deviationFreq"); }

    // АС
    double getAzimuthProgramm() const;
    void setAzimuthProgramm(const double &value);
    QString getAzimuthProgrammFieldName() { return _NAME_OF_ARG(azimuthProgramm); }

    double getElevProgramm() const;
    void setElevProgramm(const double &value);
    QString getElevProgrammFieldName() { return _NAME_OF_ARG(elevProgramm); }

    bool getIsCorrection() const;
    void setIsCorrection(bool value);
    QString getIsCorrectionFieldName() { return _NAME_OF_ARG(isCorrection); }

    double getLevelPTN() const;
    void setLevelPTN(const double &value);
    QString getLevelPTNFieldName() { return _NAME_OF_ARG(levelPTN); }

    bool getIsAntennaTD() const;
    void setIsAntennaTD(bool value);
    QString getIsTDFieldName() { return _NAME_OF_ARG(isTD); }

    QString getAzimuthFBSFieldName() { return QString("azimuthDOS"); }
    QString getAzimuthCorrectionFieldName() { return QString("azimuthCorrection"); }
    QString getElevFBSFieldName() { return QString("elevDOS"); }
    QString getElevCorrectionFieldName() { return QString("elevCorrection"); }
    QString getModeAntennaFieldName() { return QString("modeAntenna");}

    // усилители мощности
    QString getPowerFieldName() { return QString("power"); }
    QString getAttFieldName() { return QString("attenuator"); }
    QString getTempFieldName() { return QString("temp"); }
    QString getPRDinAntFieldName() { return QString("PRDinAnt"); }
    QString getPRDinLoadFieldName() { return QString("PRDinLoad"); }

    // комплекты
    QString getComplectModemFieldName() { return QString("complectModem"); }
    QString getComplectConverterFieldName() { return QString("complectConverter"); }
    QString getComplectYMFieldName() { return QString("complectYM"); }
    QString getComplectMSHYFieldName() { return QString("complectMSHY"); }
    QString getPolarPLMFieldName() { return QString("polarPLM"); }
    QString getPolarUpFieldName() { return QString("polarUp"); }
    QString getSwapLIUFieldName() { return QString("swapBSY"); }
    void changeStateComplect(const Complects comp, const bool state);

    // настройки КИС
    QString getLiterCarrierFieldName() { return QString("literCarrier"); }
    QString getLiterPNSFieldName() { return QString("literPSHS"); }
    QString getLiterOTCFieldName() { return QString("literRK"); }
    QString getStripPRMFieldName() { return QString("stripPRM"); }
    QString getCorrectionSearchFieldName() { return QString("correctionSearch"); }
    QString getCorrectionDoplerFieldName() { return QString("correctionDopler"); }
    QString getKeySCPIFieldName() { return QString("keySKZI"); }
    QString getKeyOSKFieldName() { return QString("keyBSK"); }
    QString getCloseModeFieldName() { return QString("closeMode"); }

    // компенсация доплера
    QString getDoplerByCUFieldName() { return QString("doplerByCU"); }
    QString getDoplerByAnswerFieldName() { return QString("doplerByAnswer"); }

    bool getIdCU() const;
    void setIdCU(bool value);
    QString getIdCUFieldName() { return _NAME_OF_ARG(idCU); }

    bool getLockAnswer() const;
    void setLockAnswer(bool value);
    QString getLockAnswerFieldName() { return _NAME_OF_ARG(lockAnswer); }

    uint64_t getDoplerTimeTD() const;
    void setDoplerTimeTD(const uint64_t &value);
    QString getDoplerTimeTDFieldName() { return _NAME_OF_ARG(doplerTimeTD); }

    double getCompensationCarrierTD() const;
    void setCompensationCarrierTD(const double &value);
    QString getCompensationCarrierTDFieldName() { return _NAME_OF_ARG(compensationCarrierTD); }

    double getCompensationPNSTD() const;
    void setCompensationPNSTD(const double &value);
    QString getCompensationPNSTDFieldName() { return _NAME_OF_ARG(compensationPNSTD); }

    uint64_t getDoplerTimeAnswer() const;
    void setDoplerTimeAnswer(const uint64_t &value);
    QString getDoplerTimeAnswerFieldName() { return _NAME_OF_ARG(doplerTimeAnswer); }

    bool getCalibrationMode() const;
    void setCalibrationMode(const bool &value);
    QString getCalibrationModeFieldName() { return _NAME_OF_ARG(calibrationMode); }

    double getCompensationCarrierAnswer() const;
    void setCompensationCarrierAnswer(const double &value);
    QString getCompensationCarrierAnswerFieldName() { return _NAME_OF_ARG(compensationCarrierAnswer); }

    double getCompensationPNSAnswer() const;
    void setCompensationPNSAnswer(const double &value);
    QString getCompensationPNSAnswerFieldName() { return _NAME_OF_ARG(compensationPNSAnswer); }

    // ТМИ
    QString getMode1kHzFieldName() { return QString("mode1kHz"); }
    QString getMode8kHzFieldName() { return QString("mode8kHz"); }
    QString getCounterTLMFieldName() { return QString("counterTLM"); }

    // РК
    QString getFirstSemiKitFieldName() { return QString("firstPK"); }
    QString getSecondSemiKitFieldName() { return QString("secondPK"); }
    QString getNumberOTCFieldName() { return QString("numberRK"); }
    QString getPlusOTCFieldName() { return QString("plusRK"); }
    QString getMinusOTCFieldName() { return QString("minusRK"); }
    QString getNullOTCFieldName() { return QString("nullRK"); }
    QString getSendOTCFieldName() { return QString("sendRK"); }
    QString getOOTCFieldName() { return QString("ORK"); }

    // СИ
    QString getNumberSIFieldName() { return QString("numberSI"); }
    QString getNumberPhraseSIFieldName() { return QString("numberPhraseSI"); }
    QString getPlusSIFieldName() { return QString("plusSI"); }
    QString getMinusSIFieldName() { return QString("minusSI"); }
    QString getNullSIFieldName() { return QString("nullSI"); }
    QString getNullZKVIFieldName() { return QString("nullZKV"); }
    QString getOnSIFieldName() { return QString("onSI"); }
    QString getStopSIFieldName() { return QString("stopSI"); }
    QString getIdSIFieldName() { return QString("idSI"); }

    // РКО
    QString getCurrentTempORMFieldName() { return QString("currentTempRKO"); }
    QString getCounterAngleFieldName() { return QString("counterAngle"); }
    QString getCounterDistanceFieldName() { return QString("counterDistance"); }
    QString getChangeDistanceFieldName() { return QString("changeDistance"); }
    QString getChangeAngleFieldName() { return QString("changeAngle"); }
    QString getIdDZFieldName() { return QString("idDZ"); }
    QString getCalibrationFieldName() { return QString("calibration"); }

    // Команда управления
    BaseCommandControl &getCommands();
    void setCommands(QSharedPointer<BaseCommandControl> value);
    CommandsControl getCurrentCommandControl();
    QJsonObject getJsonCommandControl();
    void setCurrentModeStation(const uint16_t currentMode);
    int16_t getParamCommandControl(const Words word);
    void setTypeSender(const TypeSender sender);
    TypeSender getTypeSender() const;

    // Специальная информация
    SpecialInformation& getSpecialInfo();
    QString getConvertPhraseSpecialInformation();
    bool unserializeSpecialInformation(QByteArray& array);

    QSharedPointer<BaseFunctionControl> getInfoFC();
    void setInfoFC(QSharedPointer<BaseFunctionControl> value);
    void createByteArrayForSendIFCT(QByteArray& array);

    // разовая команда
    SingleCommand& getSingleCommand();
    void setNumberSingleCommand(const uint16_t numCommand);
    void setTypeSingleCommand(const bool typeCommand);
    void setTypeTimeSingleCommand(const bool typeTime);
    void setDateTimeSingleCommand(const QString dateTime);

    // специальная ЦУ
    QJsonObject getJsonSpecialCC();
    SpecialCC &getSpecialCC() ;
    void setSpecialCC(const SpecialCC &value);

    bool getIsModemTD() const;
    void setIsModemTD(bool value);

    void setIsModemCortex(bool isModemCortex);

    int getRealCMDNum();
    void setRealCMDNum(int v);

    void resetParams();

    void setParamsSession();

    StructFunctionControl *getFunctionControl();

private:
    QString getNameComplectForJson(const uint8_t comp);
    QString getStringAzimuthProgramm() const;
    QString getStringElevProgramm() const;
    void initStateComplects();
};

using ParamsSingleton = Singleton<ParamsCMS>;

#endif // PARAMSCMS_H
