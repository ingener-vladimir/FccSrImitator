#ifndef IIFCSENDER_H
#define IIFCSENDER_H

#include <QObject>

class IIfcSender : public QObject
{
    Q_OBJECT
public:
    virtual ~IIfcSender() = default;
    virtual void process() = 0;
    virtual void setIsActive(bool value) = 0;
    virtual bool getIsActive() const = 0;
};

#endif // IIFCSENDER_H
