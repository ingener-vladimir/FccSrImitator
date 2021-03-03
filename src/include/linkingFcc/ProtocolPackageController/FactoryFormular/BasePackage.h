#ifndef BASEPACKAGE_H
#define BASEPACKAGE_H

/*!
    \file
    \brief Абстрактный класс наследник базового класса BasePackage
    Имплементирует общие функции работы с пакетами для всех классов наследников
    BasePackage -> IPackage
    \author Саньков Владимир
    \version 0.1
    \date сентябрь 2019 г.
*/

#include "interface/linkingFcc/IPackage.h"

class BasePackage : public IPackage
{
    static const uint8_t ENDER = 0x27;         ///< Концевик  = 0x27
    static const uint8_t ESCAPE = 0x55;        ///< Escape-символ
    static const uint8_t INVERT_ENDER = 0xD8;  ///< Инверсия
    static const uint8_t INVERT_ESCAPE = 0xAA; ///< Инверсия

public:
    BasePackage() {}
    ~BasePackage() {}

protected:
    /*!
     * \brief Подготовка сообщения
     * \param array Массив данных
     * \return Массив преобразованных данных
     *
     * Для устранения неоднозначности, при отправке в сообщение перед каждым байтом 0х27
       (начиная с первого байта заголовка без последнего байта) вводится Escape-символ с кодом 0х55,
       а символ текста, совпадающий с 0х27 – инвертируется. Аналогичная операция выполняется
       и с каждым символом сообщения, совпадающим с 0х55.
       Исходное сообщение:
       0хС0          0x55		0x51    0xС0 	 0x15          0x27   		 0x55 		0x48 	0х27
       Переданное сообщение
       0хС0          0x55 0xAA 	0x51 	0xС0	 0x15 	  0x55 0xD8	         0x55 0xAA	0x48  	0х27
     */
    QByteArray prepareData(const QByteArray &array);
};

#endif // BASEPACKAGE_H
