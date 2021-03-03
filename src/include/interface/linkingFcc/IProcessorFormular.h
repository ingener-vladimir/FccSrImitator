#ifndef IPROCESSORFORMULAR
#define IPROCESSORFORMULAR

/*!
    \file
    \brief Интерфейсный класс распаковки полученных пакетов
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QSharedPointer>
#include <QObject>
#include "IFactoryFormular.h"

class IProcessorFormular : public  QObject
{
    Q_OBJECT

public:
    virtual ~IProcessorFormular() = default;
    /*!
     * \brief Установить фабрику пакетов для формирования ответных пакетов
     * \param factory Фабрика пакетов
     */
    virtual void setFactoryFormular(QSharedPointer<IFactoryFormular> factory) = 0;
    /*!
     * \brief Распаковать полученный массив данных
     * \param array Массив байт
     */
    virtual void decodeByteArray(QByteArray &array) = 0;

    /*!
     * \brief Распаковать полученный заголовок и получить количество
     * байт для чтения
     * \param array Массив байт
     * \return размер данных для чтения header+data
     * \author Данильченко Артем
     */
    virtual int32_t decodeSizeToRead(const QByteArray &){ return 0;}

    /*!
     * \brief Размер заголовка для конкретной версии протокола
     * \author Данильченко Артем
     */
    virtual int32_t sizeHeader(){ return 0; }
    /*!
     * \brief Проверка на установку логического соединения
     * Используется только если протоколо подразумевает
     * установку логического соединения,или обмен ПКС-ОКС
     * \author Данильченко Артем
     */
    virtual bool isConnectionChecked() { return false; }

    /*!
     * \brief Сброс флага установки логического соединенения
     * \author Данильченко Артем
     */
    virtual void resetConnectionChecked() {}
    /*!
     * \brief Если в протоколе задано поле идентификатора источника
     * сообщения
     * \author Данильченко Артем
     */
    virtual uint64_t getSourceReceivedPackage(){ return 0;}
    /*!
     * \brief getByteArrayToSend получение массива байт для отправки
     * \return массив байт, вкотором упакованы все пакеты для отправки
     * \author Данильченко Артем
     */
    virtual QByteArray getByteArrayToSend(){ return QByteArray();}
};
#endif // IPROCESSORFORMULAR

