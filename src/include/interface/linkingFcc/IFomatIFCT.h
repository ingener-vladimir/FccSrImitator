#ifndef IFOMATIFCT_H
#define IFOMATIFCT_H

#include <QByteArray>

#include "../App/daq_scheme/linkingFCC/Singleton/Singleton.h"
#include "../App/daq_scheme/linkingFCC/OptionsKIS/Params/ParamsCMS.h"

class IFomatIFCT
{
public:
    virtual ~IFomatIFCT() = default;
    virtual QByteArray createArrayIFCT(const bool isActive) = 0;
};

#endif // IFOMATIFCT_H
