#ifndef CORE_H
#define CORE_H

#include "linkingFcc/LinkingFCC.h"

class Core : public QObject
{
    Q_OBJECT

    LinkingFCC _linkingFCC;
    QTimer _timer;

    void update();
public:
    Core();
    ~Core();

};

#endif // CORE_H
