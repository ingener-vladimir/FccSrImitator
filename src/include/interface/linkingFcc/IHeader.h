#ifndef IHEADER
#define IHEADER

/*!
    \file
    \brief Интерфейсный класс унифицированного заголовка пакета
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.

*/

#include <QByteArray>
#include <QString>

class IHeader
{
public:
    virtual ~IHeader() = default;

    /*!
     * \brief Сериализует данные для отправки
     * \return Данные в виде массива байт
     */
    virtual QByteArray serialize() = 0;
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] data Полученные данные
     * \return Указатель на родительский класс заголовка
     */
    virtual IHeader* unserialize(const QByteArray &data) = 0;
    /*!
     * \brief Возвращает размер заголовка
     * \return Размер заголовка
     */
    virtual uint32_t sizeHeader() const = 0;

    /*!
     * \brief Установка размера данных в байтах
     * \author Данильченко Артём
     * \return Размер данных
     */
    virtual void setLengthData( int32_t) {}
    /*!
     * \brief Возвращает размер данных в байтах
     * \return Размtр данных
     */
    virtual int32_t lengthData() const = 0;

    /*!
     * \brief Возвращает размер данных+заголовок в байтах
     * \author Данильченко Артём
     * \return Размер данных+заголовок
     */
    virtual int32_t lengthDataWithHeader() { return 0; }

    /*!
     * \brief Получить версию протокола
     * \author Данильченко Артём
     * \return номер версии протокола
     */
    virtual uint8_t getVersionProtocol(){ return 0; }
    /*!
     * \brief  вывести в консоль данные о заголовке
     * \author Данильченко Артём
     * \return номер версии протокола
     */
    virtual void toDebug(QString){}
    /*!
     * \brief  Флаг валидности заголовка
     * \author Данильченко Артём
     * \return результат проверки валидности
     */
    virtual bool isValidHeader(){ return false; }
    /*!
     * \brief  тип сообщения в заголовке
     * \author Данильченко Артём
     * \return код типа заголовка пакета
     */
    virtual uint16_t getHeaderType() { return 0; }
};

#endif // IHEADER

