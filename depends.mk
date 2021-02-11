HTTPServer.o: HTTPServer.c HTTPServer.h WebSocketServer.h \
 WebSocketHTTPConfig.h HTTPServer/HTTPServerGetThreadID.c \
 HTTPServer/HTTPServerEventHandler.c HTTPServer/HTTPServerThread.c \
 HTTPServer/HTTPServerStart.c HTTPServer/HTTPServerInitialize.c
Log.o: Log.c Log.h Log/LogInitialize.c Log/LogSetFilename.c \
 Log/LogWrite.c Log/LogClear.c
main.o: main.c main.h mainconfig.h HTTPServer.h UserInterfaceServer.h \
 WebSocketServer.h WebSocketHTTPConfig.h NetworkMonitorServer.h Log.h \
 MainProcessCommandLine.c MainDisplayHelp.c MainInitialize.c
MainDisplayHelp.o: MainDisplayHelp.c
MainInitialize.o: MainInitialize.c
MainProcessCommandLine.o: MainProcessCommandLine.c
NetworkMonitorServer.o: NetworkMonitorServer.c NetworkMonitorServer.h \
 UserInterfaceServer.h \
 NetworkMonitorServer/NetworkMonitorServerGetThreadID.c \
 NetworkMonitorServer/NetworkMonitorServerThread.c \
 NetworkMonitorServer/NetworkMonitorServerStart.c \
 NetworkMonitorServer/NetworkMonitorInitialize.c \
 NetworkMonitorServer/NetworkMonitorPrintData.c \
 NetworkMonitorServer/NetworkMonitorPrintICMPPacket.c \
 NetworkMonitorServer/NetworkMonitorPrintUDPPacket.c \
 NetworkMonitorServer/NetworkMonitorPrintTCPPacket.c \
 NetworkMonitorServer/NetworkMonitorPrintIPHeader.c \
 NetworkMonitorServer/NetworkMonitorPrintEthernetHeader.c \
 NetworkMonitorServer/NetworkMonitorProcessPacket.c \
 NetworkMonitorServer/NetworkMonitorInterface.c \
 NetworkMonitorServer/NetworkMonitorSetIPAddress.c \
 NetworkMonitorServer/NetworkMonitorSetRoute.c \
 NetworkMonitorServer/NetworkMonitorGenericIOCtrlCall.c \
 NetworkMonitorServer/NetworkMonitorGetNetworkInterfaces.c \
 NetworkMonitorServer/NetworkMonitorCreateSocket.c
UserInterfaceServer.o: UserInterfaceServer.c UserInterfaceServer.h \
 UserInterfaceServer/UserInterfaceServerGetThreadID.c \
 UserInterfaceServer/UserInterfaceProcessCommandQuit.c \
 UserInterfaceServer/UserInterfaceProcessCommandHelp.c \
 UserInterfaceServer/UserInterfaceProcessCommand.c \
 UserInterfaceServer/UserInterfaceParseCommandLine.c \
 UserInterfaceServer/UserInterfaceServerThread.c \
 UserInterfaceServer/UserInterfaceServerStart.c \
 UserInterfaceServer/UserInterfaceServerInitialize.c
WebConnection.o: WebConnection.c WebConnection.h WebSocketHTTPConfig.h \
 WebConnection/WebConnectionTimeUpdate.c \
 WebConnection/WebConnectionListGetByIndex.c \
 WebConnection/WebConnectionListDisplay.c \
 WebConnection/WebConnectionListCount.c \
 WebConnection/WebConnectionListFind.c \
 WebConnection/WebConnectionListRemove.c \
 WebConnection/WebConnectionListAppend.c \
 WebConnection/WebConnectionListCreate.c \
 WebConnection/WebConnectionClose.c WebConnection/WebConnectionDestroy.c \
 WebConnection/WebConnectionCreate.c
WebSocketHTTPConfig.o: WebSocketHTTPConfig.c WebSocketHTTPConfig.h
WebSocketServer.o: WebSocketServer.c WebSocketServer.h WebConnection.h \
 UserInterfaceServer.h main.h WebSocketHTTPConfig.h \
 NetworkMonitorServer.h
