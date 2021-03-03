#ifndef PACKAGEDIRECTIVE20_H
#define PACKAGEDIRECTIVE20_H

/*!
    \file
    \brief Класс-наследник для создания пакета по директиве 20
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include <QTextCodec>
#include <QTextDecoder>

#include "interface/linkingFcc/IPackage.h"
#include "linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h"

class PackageDirective20 : public IPackage
{

public:
    /*!
     * \brief Конструктор
     * \param array Массив данных
     */
    PackageDirective20(QByteArray& array);
    /*!
     * \brief Сериализует данные для отправки
     * \return Данные в виде массива байт
     */
    QByteArray serialize() override { return QByteArray(); }
    /*!
     * \brief Распаковывает полученные данные
     * \param[in] array Полученные данные
     */
    void unserialize(QByteArray &) override {}

private:
    /*!
     * \brief Перекодировать принятое сообщение
     */
    //TODO: реализовать перекодировку сообщения
    void decodeMessage(QByteArray &array);
};

#endif // PACKAGEDIRECTIVE20_H
