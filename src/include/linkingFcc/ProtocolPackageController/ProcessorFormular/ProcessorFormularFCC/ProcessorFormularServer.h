#ifndef PROCESSORFORMULARFCC_H
#define PROCESSORFORMULARFCC_H

/*!
    \file
    \brief Класс-наследник распаковки принятых пакетов из ЦУП
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IProcessorFormular.h"
#include "Data/PackageDirective03.h"
#include "Data/PackageDirective12.h"
#include "Data/PackageDirective16SpecialInfo.h"
#include "Data/PackageDirective16OneTimeCommand.h"
#include "Data/PackageDirective16CommandControl.h"
#include "Data/PackageDirective20.h"
#include "linkingFcc/GUIExchangeAdapter.h"

class ProcessorFormularServer : public IProcessorFormular
{
    QSharedPointer<IFactoryFormular> _factory{nullptr}; ///< Фабрика пакетов
    QSharedPointer<GUIExchangeAdapter> _guiExchangeAdapter{nullptr};           ///< Отправитель параметров станции

    static int numberClient;                            ///< Номер клиента(увеличивается на 1 при новом подключении)
    uint16_t _currentNumber{0};                         ///< Текущий номер клиента
    bool _needSendTicket{false};                        ///< Нужно ли отправлять квитанцию
    static const uint16_t COOL_APPARAT = 649;

public:
    ProcessorFormularServer(QSharedPointer<GUIExchangeAdapter> guiExchangeAdapter);
    ~ProcessorFormularServer();
    /*!
     * \brief Установить фабрику пакетов
     * \param factory Фабрика пакетов
     */
    void setFactoryFormular(QSharedPointer<IFactoryFormular> factory) override;
    /*!
     * \brief Распаковать полученный массив данных
     * \param array Массив байт
     */
    void decodeByteArray(QByteArray &array) override;
    /*!
     * \brief Установить отправителя параметров станции
     * \param senderParamsStation Отправитель параметров станции
     */
    void setGuiExchangeAdapter(QSharedPointer<GUIExchangeAdapter> guiExchangeAdapter);

private:
    /*!
     * \brief Проверка валидности параметров текущей сессии с КА
     * \param message Полученые значения
     * \param params Текущие значения
     */
    void checkValidParamsSession(Header &message, ParamsCMS& params);
    /*!
     * \brief Нужно ли проверять полученый пакет на валидность параметров
     * \param dir Номер директивы
     * \param params Текущие параметры
     * \return Флаг, нужно ли проверять
     */
    bool needCheck(Directive dir, ParamsCMS &params);
    /*!
     * \brief Распаковка данных, принятых по директиве 16
     * \param header Заголовок принятого пакета
     * \param array Массив данных
     * \param params Текущие параметры
     */
    void unserializeDataPD16(Header &header,
                             QByteArray &array,
                             ParamsCMS &params);
};

#endif // PROCESSORFORMULARFCC_H
