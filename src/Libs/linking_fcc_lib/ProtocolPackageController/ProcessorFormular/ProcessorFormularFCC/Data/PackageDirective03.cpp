#include "linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective03.h"

PackageDirective03::PackageDirective03(QByteArray &array)
    : _arrayData(array.right(array.size() - sizeof(daq::Header)))
{
    writeTLM();
}

//TODO: сюда добавить функцию записи ТМИ в файл, посмотреть в старом проекте
void PackageDirective03::writeTLM()
{

}
