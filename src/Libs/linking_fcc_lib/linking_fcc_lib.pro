#-------------------------------------------------
#
# Project created by QtCreator 2021-02-07T15:04:15
#
#-------------------------------------------------

QT       += core network

TARGET = linking_fcc_lib
TEMPLATE = lib

DEFINES += LIB_LINKING_FCC_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUIExchangeAdapter.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective112Angle.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective112Distance.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective112Speed.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective150.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective152New.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective152Old.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective155.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective198.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageTicket.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFCC/FactoryFormularFCC.cpp \
    ProtocolPackageController/FactoryFormular/BasePackage.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormular.cpp \
    FileWorker/Controllers/ControllerTargetDesignation.cpp \
    FileWorker/BaseFileWorker.cpp \
    FileWorker/FileWorkerORM.cpp \
    FileWorker/FileWorkerSI.cpp \
    FileWorker/FileWorkerTD.cpp \
    FileWorker/FileWorkerTmi.cpp \
    LinkingFCC.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/ProcessorFormularServer.cpp \
    ProtocolPackageController/ProtocolPackageController.cpp \
    ProtocolPackageController/network/TcpClient.cpp \
    ProtocolPackageController/network/TcpNetworkWorker.cpp \
    ProtocolPackageController/network/TcpServer.cpp \
    ProtocolPackageController/network/TcpThreadSocket.cpp \
#    ProtocolPackageController/network/client/NetworkWorker.cpp \
#    ProtocolPackageController/network/client/TcpClientThreadSocket.cpp \
    information/CommandControl/BaseCommandControl.cpp \
    information/CommandControl/CommandControl.cpp \
    information/CommandControl/CommandControl649.cpp \
    information/CommandControl/FactoryCommandControl.cpp \
    information/FunctionControl/BaseFunctionControl.cpp \
    information/FunctionControl/FunctionControl330.cpp \
    information/FunctionControl/FunctionControl344.cpp \
    information/FunctionControl/FunctionControl345.cpp \
    information/FunctionControl/FunctionControl346.cpp \
    information/FunctionControl/FunctionControl649.cpp \
    information/FunctionControl/InfoFunctionControl.cpp \
    information/FunctionControl/StructFunctionControl.cpp \
    information/Params/FactoryParams.cpp \
    information/Params/ParamsCMS.cpp \
    information/ParamsController/BaseParamsController.cpp \
    information/ParamsController/FactoryParamsController.cpp \
    information/ParamsController/NullParamsController.cpp \
    information/ParamsController/ParamsController.cpp \
    information/ParamsController/ParamsController649.cpp \
    information/SingleCommand/SingleCommand.cpp \
    information/SpecialCommandControl/SpecialCC.cpp \
    information/SpecialInformation/SpecialInformation.cpp \
    Journals/JournalCommon.cpp \
    Parser/BaseParser.cpp \
    Parser/ParserAmplifier.cpp \
    Parser/ParserAntenna.cpp \
    Parser/ParserEvents.cpp \
    Parser/ParserFactory.cpp \
    Parser/ParserMeteo.cpp \
    Parser/ParserModem.cpp \
    Parser/ParserVirtual.cpp \
    Parser/ParseThread.cpp \
    Parser/ParseWorker.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective03.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective12.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16CommandControl.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16OneTimeCommand.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16SpecialInfo.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective20.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective25.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective98.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormular.cpp \
    utils/Degree.cpp \
    information/DoplerFrequencyOffset/DoplerFrequencyOffset.cpp \
    information/PropagationSignalDelay/PropagationSignalDelay.cpp \
    information/Telemetry/Telemetry.cpp \
    information/SpecialInformation/fcc-sr/SpecialInformationSr.cpp \
    information/FunctionControl/fcc-sr/FunctionControlSr.cpp \
    information/Params/fcc-sr/ParamsSr.cpp \
    information/CommandControl/fcc-sr/ControlCommandSr.cpp \
    utils/NetworkPackageUtils.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularServerFccSr/ProcessorFormularServerFccSr.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/FactoryFormularFccSr.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularServerFccSr/Data/PackageTelemetry.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularServerFccSr/Data/PackagePropagationSignalDelay.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularServerFccSr/Data/PackageDoplerFrequencyOffset.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularServerFccSr/Data/PackageFunctionControl.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSpecialInformation.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSingleCommand.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageControlCommand.cpp \
    ProtocolPackageController/ProcessorFormular/ProcessorFormularServerFccSr/ProcessorFormularClientFccSr.cpp \
    Senders/Ifc/IfcSender.cpp \
    Senders/ParamsStationSender.cpp \
    Senders/TicketsSender.cpp \
    Senders/TmiSender.cpp \
    Senders/Ifc/BaseIfcSender.cpp \
    Senders/Ifc/IfcSenderFactory.cpp \
    Senders/Ifc/IfcSenderSr.cpp \
    ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageTicketSr.cpp \
    information/SingleCommand/fcc_sr/SingleCommandSr.cpp \
    utils/DateTimeUtils.cpp
HEADERS += \
    ../../include/linkingFcc/GUIExchangeAdapter.h \
    ../../include/linkingFcc/LinkingFCC.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/BasePackage.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormular.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective112Angle.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective112Distance.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective112Speed.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective150.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective152New.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective152Old.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective155.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageDirective198.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/PackageTicket.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/StructPackageDirective112Angle.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/StructPackageDirective112Distance.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/StructPackageDirective112Speed.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/StructPackageDirective152New.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/StructPackageDirective152Old.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Data/StructPackageDirective155.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/FactoryFormularFCC.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFCC/Header/Header.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormular.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective03.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective12.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16CommandControl.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16OneTimeCommand.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective16SpecialInfo.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective20.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective25.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/Data/PackageDirective98.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFCC/ProcessorFormularServer.h \
    ../../include/linkingFcc/ProtocolPackageController/ProtocolPackageController.h \
    ../../include/linkingFcc/ProtocolPackageController/network/TcpClient.h \
    ../../include/linkingFcc/ProtocolPackageController/network/TcpNetworkWorker.h \
    ../../include/linkingFcc/ProtocolPackageController/network/TcpServer.h \
    ../../include/linkingFcc/ProtocolPackageController/network/TcpThreadSocket.h \
    ../../include/linkingFcc/FileWorker/Controllers/ControllerTargetDesignation.h \
    ../../include/linkingFcc/FileWorker/BaseFileWorker.h \
    ../../include/linkingFcc/FileWorker/FileWorkerORM.h \
    ../../include/linkingFcc/FileWorker/FileWorkerSI.h \
    ../../include/linkingFcc/FileWorker/FileWorkerTD.h \
    ../../include/linkingFcc/FileWorker/FileWorkerTmi.h \
#    ../../include/linkingFcc/ProtocolPackageController/network/client/NetworkWorker.h \
#    ../../include/linkingFcc/ProtocolPackageController/network/client/TcpClientThreadSocket.h \
    ../../include/linkingFcc/infornation/CommandControl/BaseCommandControl.h \
    ../../include/linkingFcc/infornation/CommandControl/CommandControl.h \
    ../../include/linkingFcc/infornation/CommandControl/CommandControl649.h \
    ../../include/linkingFcc/infornation/CommandControl/CommandControlEnum.h \
    ../../include/linkingFcc/infornation/CommandControl/FactoryCommandControl.h \
    ../../include/linkingFcc/infornation/FunctionControl/BaseFunctionControl.h \
    ../../include/linkingFcc/infornation/FunctionControl/EnumsFunctionControl.h \
    ../../include/linkingFcc/infornation/FunctionControl/FunctionControl330.h \
    ../../include/linkingFcc/infornation/FunctionControl/FunctionControl344.h \
    ../../include/linkingFcc/infornation/FunctionControl/FunctionControl345.h \
    ../../include/linkingFcc/infornation/FunctionControl/FunctionControl346.h \
    ../../include/linkingFcc/infornation/FunctionControl/FunctionControl649.h \
    ../../include/linkingFcc/infornation/FunctionControl/InfoFunctionControl.h \
    ../../include/linkingFcc/infornation/FunctionControl/StructFunctionControl.h \
    ../../include/linkingFcc/infornation/Params/FactoryParams.h \
    ../../include/linkingFcc/infornation/Params/ParamsCMS.h \
    ../../include/linkingFcc/infornation/ParamsController/BaseParamsController.h \
    ../../include/linkingFcc/infornation/ParamsController/FactoryParamsController.h \
    ../../include/linkingFcc/infornation/ParamsController/NullParamsController.h \
    ../../include/linkingFcc/infornation/ParamsController/ParamsController.h \
    ../../include/linkingFcc/infornation/ParamsController/ParamsController649.h \
    ../../include/linkingFcc/infornation/SingleCommand/SingleCommand.h \
    ../../include/linkingFcc/infornation/SpecialCommandControl/SpecialCC.h \
    ../../include/linkingFcc/infornation/SpecialInformation/SpecialInformation.h \
    ../../include/linkingFcc/Structs/StructBandTLM.h \
    ../../include/linkingFcc/Structs/Words.h \
    ../../include/linkingFcc/Journals/JournalCommon.h \
    ../../include/linkingFcc/Parser/BaseParser.h \
    ../../include/linkingFcc/Parser/IParserParams.h \
    ../../include/linkingFcc/Parser/ParserAmplifier.h \
    ../../include/linkingFcc/Parser/ParserAntenna.h \
    ../../include/linkingFcc/Parser/ParserEvents.h \
    ../../include/linkingFcc/Parser/ParserFactory.h \
    ../../include/linkingFcc/Parser/ParserMeteo.h \
    ../../include/linkingFcc/Parser/ParserModem.h \
    ../../include/linkingFcc/Parser/ParserVirtual.h \
    ../../include/linkingFcc/Parser/ParseThread.h \
    ../../include/linkingFcc/Parser/ParseWorker.h \
    ../../include/linkingFcc/Singleton/Singleton.h \
    ../../include/linkingFcc/Structs/CodeTicket.h \
    ../../include/linkingFcc/Structs/Directive.h \
    ../../include/linkingFcc/Structs/StructHeader.h \
    ../../include/linkingFcc/Structs/TmiFormat.h \
    ../../include/linkingFcc/Structs/TypeInformation.h \
    ../../include/interface/linkingFcc/IFactoryFormular.h \
    ../../include/interface/linkingFcc/IFileWorker.h \
    ../../include/interface/linkingFcc/IHeader.h \
    ../../include/interface/linkingFcc/IJournal.h \
    ../../include/interface/linkingFcc/INetworkWorker.h \
    ../../include/interface/linkingFcc/IPackage.h \
    ../../include/interface/linkingFcc/IPackageController.h \
    ../../include/interface/linkingFcc/IParamsController.h \
    ../../include/interface/linkingFcc/IProcessorFormular.h \
    ../../include/linkingFcc/linking_fcc_lib_global.h \
    ../../include/utils/tochar.h \
    ../../include/linkingFcc/infornation/CommandControl/fcc-sr/ListControlCommand.h \
    ../../include/linkingFcc/infornation/DoplerFrequencyOffset/DoplerFrequencyOffset.h \
    ../../include/linkingFcc/infornation/PropagationSignalDelay/PropagationSignalDelay.h \
    ../../include/linkingFcc/infornation/SingleCommand/fcc_sr/Periodicity.h \
    ../../include/linkingFcc/infornation/Telemetry/Telemetry.h \
    ../../include/utils/BitUtils.h \
    ../../include/linkingFcc/infornation/SpecialInformation/fcc-sr/SpecialInformationSr.h \
    ../../include/linkingFcc/infornation/FunctionControl/fcc-sr/FunctionControlSr.h \
    ../../include/linkingFcc/infornation/CommandControl/fcc-sr/ControlCommandSr.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/ProcessorFormularServerFccSr.h \
    ../../include/utils/NetworkPackageUtils.h \
    ../../include/linkingFcc/infornation/Params/fcc-sr/ParamsSr.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/FactoryFormularFccSr.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Header/HeaderSr.h \
    ../../include/linkingFcc/Structs/StructHeaderSr.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageDoplerFrequencyOffset.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageFunctionControl.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackagePropagationSignalDelay.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/Data/PackageTelemetry.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/StructFunctionControlSr.h \
    ../../include/linkingFcc/infornation/Telemetry/StructTelemetry.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSpecialInformation.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageSingleCommand.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageControlCommand.h \
    ../../include/linkingFcc/infornation/CommandControl/fcc-sr/StructControlCommand.h \
    ../../include/linkingFcc/infornation/SingleCommand/fcc_sr/StructSingleCommand.h \
    ../../include/linkingFcc/infornation/SpecialInformation/StructSpecialInformation.h \
    ../../include/linkingFcc/ProtocolPackageController/ProcessorFormular/ProcessorFormularFccSr/ProcessorFormularClientFccSr.h \
    ../../include/linkingFcc/infornation/CommandControl/StructControlCommand.h \
    ../../include/linkingFcc/infornation/SingleCommand/StructSingleCommand.h \
    ../../include/linkingFcc/Senders/Ifc/IfcSender.h \
    ../../include/linkingFcc/Senders/ParamsStationSender.h \
    ../../include/linkingFcc/Senders/TicketsSender.h \
    ../../include/linkingFcc/Senders/TmiSender.h \
    ../../include/linkingFcc/Senders/Ifc/IfcSenderSr.h \
    ../../include/interface/linkingFcc/IIfcSender.h \
    ../../include/linkingFcc/Senders/Ifc/BaseIfcSender.h \
    ../../include/linkingFcc/Senders/Ifc/IfcSenderFactory.h \
    ../../include/utils/ValueToByteArray.h \
    ../../include/linkingFcc/ProtocolPackageController/FactoryFormular/FactoryFormularFccSr/Data/PackageTicketSr.h \
    ../../include/linkingFcc/infornation/SingleCommand/fcc_sr/SingleCommandSr.h \
    ../../include/utils/DateTimeUtils.h \
    ../../include/linkingFcc/Structs/TicketDirective.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include( ../../../common.pri )
include( ../../../lib.pri )
