#ifndef TCPTHREADSOCKET_H
#define TCPTHREADSOCKET_H

/*!
    \file
    \brief Класс для работы с tcp сокетом
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QObject>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QMutex>
#include <QHostAddress>

class TcpThreadSocket : public QObject
{
    Q_OBJECT

    QList<QByteArray> _listData; ///< Список принятых пакетов
    QMutex _mutex;               ///< Мьютекс для синхронизации работы со списком пакетов

    const int8_t END_DATAGRAMM_SYMBOL = 0x27;
    QByteArray buffer;

protected:
    QTcpSocket _socket;            ///< Сокет
public:
    /*!
     * \brief Конструктор
     * \param socketDescriptor Дескриптор
     *
     * В конструкторе происходит перемещение сокета в отдельный поток
     */
    TcpThreadSocket(quintptr socketDescriptor);
    TcpThreadSocket();
    ~TcpThreadSocket();
    /*!
     * \brief Остановить работу потока
     */
    void stop();

    void connected();
    /*!
     * \brief Отправить данные по сети
     * \param data Массив данных
     */
    void send(const QByteArray &data);
    /*!
     * \brief Получить список принятых пакетов
     * \return Список пакетов
     */
    QList<QByteArray> listData();
    /*!
     * \brief Проверить статус сокета
     * \return Статус
     */
    inline bool isOpen() { return _socket.isOpen(); }

    inline QString hostAddress() { return QHostAddress(_socket.peerAddress().toIPv4Address()).toString(); }

    QTcpSocket& socket();

public slots:
    /*!
     * \brief Вызывается при получении новых данных
     */
    void onReadyRead();

signals:
    /*!
     * \brief Отправляется при завершении работы потока
     * \param desc Дескриптор сокета
     */
    void finished();
};

#endif // TCPTHREADSOCKET_H
