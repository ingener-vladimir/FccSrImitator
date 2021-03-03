#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>
#include <QUuid>
#include <QSharedPointer>

class QUuid;
class QString;
class QIcon;

namespace daq
{

enum PLUGIN_CONDITION
{
    NOT_LOAD = 0,
    LOAD
};

class IDevice;

class IPlugin
{
public:
    virtual ~IPlugin() {}
	
    virtual QUuid pluginUuid() const = 0;

    virtual QUuid deviceUuid() const = 0;

	virtual QString name() const = 0;
	virtual QString categoryName() const = 0;
	virtual QIcon icon() const = 0;

    virtual QSharedPointer<IDevice> getDevice(QUuid,
                                              bool log = false) = 0;
};

}//namespace

Q_DECLARE_INTERFACE(daq::IPlugin,"com.nik135.Daq_gui.IPlugin/2.0")

#endif
