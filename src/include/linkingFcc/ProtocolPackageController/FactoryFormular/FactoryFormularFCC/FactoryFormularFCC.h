#ifndef FACTORYFORMULARFCC_H
#define FACTORYFORMULARFCC_H

/*!
    \file
    \brief Класс-наследник для создания списка пакетов для отправки в ЦУП
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QDirIterator>

#include "interface/linkingFcc/IFactoryFormular.h"
#include "Header/Header.h"
#include "Data/PackageTicket.h"
#include "Data/PackageDirective150.h"
#include "Data/PackageDirective152New.h"
#include "Data/PackageDirective152Old.h"
#include "Data/PackageDirective155.h"
#include "Data/PackageDirective198.h"
#include "Data/PackageDirective112Speed.h"
#include "Data/PackageDirective112Distance.h"
#include "Data/PackageDirective112Angle.h"
#include "linkingFcc/FileWorker/FileWorkerORM.h"
#include "linkingFcc/Structs/TmiFormat.h"
#include "linkingFcc/infornation/Params/ParamsCMS.h"


class FactoryFormularFCC : public IFactoryFormular
{
    QMutex _mutex;                              ///< Мюьтек для синхронизации работы со списком пакетов
    uint32_t _msg_num{1};                       ///< Номер текущего сообщения
    QList<QSharedPointer<IPackage>> _list_pack; ///< Список пакетов для отправки
    Header _lastHeader;                         ///< Заголовок последнего принятого пакета

    static const int CHUNK_SIZE = 65500;        ///< Максимальная длина куска данных ДЗУ
    static const int NAME_FILE_SIZE = 3;        ///< Количество символов в имени файла, разделенных "_"
    const QString SEPARATOR = "_";              ///< Разделитель
    /*!
     * \brief Получить номер следующего сообщения
     * \return Номер сообщения
     */
    uint32_t getMessageNumber();

public:
    FactoryFormularFCC() {}
    ~FactoryFormularFCC() {}

    void setSeansPrm(uint16_t nSeansa, uint16_t nVitka);

    /*!
     * \brief Получение списка формуляров для отправки по сети
     * \return Список пакетов
     */
    QList<QSharedPointer<IPackage>> takeListPackage() override;

    /*!
     * \brief Создать квитанцию
     * \param header Заголовок отправляемой квитанции
     */
    void addTicket(Header& header);
    //
    /*!
     * \brief Создать пакет с выдачей ТМИ в одном из форматов директивы 152
     * \param format Формат ТМИ
     * \param array Массив данных
     */
    void addPackageDirective152(const TmiFormat format, const QByteArray &array);
    /*!
     * \brief Считать данные из ДЗУ и отправить формате директивы 112
     * \param Заголовок отправляемого пакета
     * \param Дата выборки
     * \param Время выборки
     */
    void addPackageDirective112(Header& header, uint16_t data, uint32_t time);
    /*!
     * \brief Считать файл или состав каталога и отправить формате директивы 198
     * \param Заголовок отправляемого пакета
     * \param Имя файла или каталога
     */
    void addPackageDirective198(Header& header, QString name);
    /*!
     * \brief Создать сообщение Абонента
     * \param Сообщение абонента
     */
    void addPackageDirective150(QString message);
    /*!
     * \brief Создать сообщение ИФКТ
     * \param array Массив данных
     */
    void addPackageDirective155(QByteArray &array);
    /*!
     * \brief Установить КА
     * \param lastKA КА
     */
    void setLastKA(const int16_t &lastKA);
    /*!
     * \brief Установить код заголовка
     * \param lastKA Код
     */
    void setCode(const CodeTicket code);

    void setNipNumber(int16_t nip);

    void setLastHeader(const Header &lastHeader);
    Header &getLastHeader();

private:
    /*!
     * \brief Получить данные ТМИ
     * \param arrayData Массив данных
     * \param data Дата выборки
     * \param time Время выборки
     */
    QVector<QByteArray> readDZYbyType(TypeFileORM type,
                                      const uint16_t data,
                                      const uint32_t time);
    /*!
     * \brief Прочитать файл по переданному имени
     * \param Имя файла
     * \return Массив прочитанных данных из файла
     */
    QByteArray readFile(QString name);

    // IFactoryFormular interface
public:
    TypeFactory getTypeFactoryFormular() override;
};

#endif // FACTORYFORMULARFCC_H
