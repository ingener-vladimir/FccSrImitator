#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective20.h"

PackageDirective20::PackageDirective20(QByteArray &array)
{
    QByteArray arr = array.right(array.size() - sizeof(daq::Header));
    decodeMessage(arr);
}

void PackageDirective20::decodeMessage(QByteArray &array)
{
    QTextCodec *codec_1251 = QTextCodec::codecForName("Windows-1251");
    QString string = codec_1251->toUnicode(array);

    QTextCodec *codec_utf8 = QTextCodec::codecForName("UTF-8");
    QString encodedString_utf8 = codec_utf8->fromUnicode(string);
}

