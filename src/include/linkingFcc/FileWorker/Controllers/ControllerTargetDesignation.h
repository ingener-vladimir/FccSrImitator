#ifndef CONTROLLERTARGETDESIGNATION_H
#define CONTROLLERTARGETDESIGNATION_H

#include <QDateTime>

#include "../FileWorkerTD.h"

class ControllerTargetDesignation
{
    static const int MAX_COUNT_SECS = (86400 * 10);

public:
    ControllerTargetDesignation() {}

    QString findLastTargetDesignation(int KA);
    QString validateTargetDestination(const QString &array, int KA);
};

#endif // CONTROLLERTARGETDESIGNATION_H
