#include "utils/NetworkPackageUtils.h"

/*! Для устранения неоднозначности, при отправке в сообщение перед каждым байтом 0х27
    (начиная с первого байта заголовка без последнего байта) вводится Escape-символ с кодом 0х55,
    а символ текста, совпадающий с 0х27 – инвертируется. Аналогичная операция выполняется
    и с каждым символом сообщения, совпадающим с 0х55. На приемном конце выполняется обратная операция
    Переданное сообщение
    0хС0          0x55 0xAA 	0x51 	0xС0	 0x15 	  0x55 0xD8	         0x55 0xAA	0x48  	0х27
    Распакованное сообщение:
    0хС0          0x55		0x51        0xС0	 	 0x15          0x27   			0x55       	 	0х48 	0х27
*/
QByteArray NetworkPackageUtils::unescapeImcomingMessage(const QByteArray& array)
{
    QByteArray res;
    int i{0};

    while(i < array.size() - 1)
    {
        if(array.at(i) == (char)ESCAPE)
        {
            if(array.at(i + 1) == (char)INVERT_ESCAPE)
                res.append((char)ESCAPE);
            else if(array.at(i + 1) == (char)INVERT_ENDER)
                res.append((char)ENDER);
            i += 2;
        }
        else
        {
            res.append(array.at(i));
            ++i;
        }
    }

    return res;
}
