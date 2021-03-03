#ifndef HEADER_H
#define HEADER_H

/*!
    \file
    \brief Класс-наследник для создания заголовка отправляемых пакетов в ЦУП
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IHeader.h"
#include "linkingFcc/Structs/StructHeaderSr.h"

class HeaderSr : public IHeader
{
    union
    {
        sr::HeaderSr _header;
        uint8_t _data[sizeof(sr::HeaderSr)]{0};
    };

     static const uint8_t ESCAPE = 192;

public:
    HeaderSr();
    /*!
     * \brief Конструктор создания заголовка
     * \param NDIR Номер директории
     * \param msgNum Номер передаваемого пакета
     * \param prevMsgNum Номер последнего принятого пакета из ЦУП
     * \param NFORM Вид информации
     * \param LenInfo Длина информации
     * \param Code Код квитанции на директиву или циклический номер инициативного сообщения ЦУП
     *
     * Принимает в качестве аргументов значения полей заголовка
     */
    HeaderSr(const Directive NDIR,
           const uint32_t msgNum,
           const uint32_t prevMsgNum,
           const TypeInfo NFORM,
           const int16_t LenInfo,
           const CodeTicket Code);
    /*!
     * \brief Конструктор
     * \param array Массив данных
     *
     * Копирует sizeof(daq::Header) данных из массива
     */
    HeaderSr(const QByteArray & array);

    HeaderSr(HeaderSr &header);

    /*!
     * \brief Сериализует данные для отправки
     * \return Данные в виде массива байт
     */
    QByteArray serialize() override;
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] data Полученные данные
     * \return Указатель на родительский класс заголовка
     */
    IHeader *unserialize(const QByteArray &) override;
    /*!
     * \brief Возвращает размер заголовка
     * \return Размер заголовка
     */
    uint32_t sizeHeader() const override;
    /*!
     * \brief Возвращает размер данных в байтах
     * \return Размер данных
     */
    int32_t lengthData() const override;
    /*!
     * \brief Получить стркутуру заголовка
     * \return Структура заголовка
     */
    sr::HeaderSr &getHeader();
};

#endif // HEADER_H
