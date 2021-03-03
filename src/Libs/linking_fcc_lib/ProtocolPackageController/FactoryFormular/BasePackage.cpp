#include "linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h"

QByteArray BasePackage::prepareData(const QByteArray& array)
{
    QByteArray res;
    for(int i = 0; i < array.size(); ++i)
    {
        if(array.at(i) == char(ENDER))
        {
            res.append(char(ESCAPE));
            res.append(char(INVERT_ENDER));
        }

        else if(array.at(i) == char(ESCAPE))
        {
            res.append(char(ESCAPE));
            res.append(char(INVERT_ESCAPE));
        }
        else
            res.append(array.at(i));
    }
    res.append(char(ENDER));

    return res;
}
