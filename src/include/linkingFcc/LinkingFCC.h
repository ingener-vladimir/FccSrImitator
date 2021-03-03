#ifndef LINKINGFCC_H
#define LINKINGFCC_H
#include "linking_fcc_lib_global.h"
#include "interface/linkingFcc/IProcessorFormular.h"
#include "interface/linkingFcc/IFactoryFormular.h"

#include <bits/unique_ptr.h>
#include "linkingFcc/ProtocolPackageController/ProtocolPackageController.h"
#include "linkingFcc/ProtocolPackageController/network/TcpServer.h"

class LIB_linkingFccSHARED_EXPORT LinkingFCC
{
    QSharedPointer<IPackageController> _packageController{nullptr};
    QSharedPointer<GUIExchangeAdapter> _guiExchangeAdapter{nullptr};
    //сервер обмена
    std::unique_ptr<TcpServer> _server{nullptr};

    //сервер обмена
    std::unique_ptr<TcpClient> _client{nullptr};

public:
    LinkingFCC();

    void createServer(quint16 port, TypeFactory type);
    void createClient(QString host, uint16_t port, TypeFactory type);

    QSharedPointer<GUIExchangeAdapter> guiExchangeAdapter() const;
    QSharedPointer<IPackageController> packageController() const;
};

#endif // LINKINGFCC_H
