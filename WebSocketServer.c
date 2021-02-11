/*****************************************************************************
 * FILE NAME    : WebSocketServer.c
 * DATE         : January 7 2021
 * PROJECT      : NONE
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <JSONIF.h>
#include <JSONOut.h>
#include <StringUtils.h>
#include <MemoryManager.h>
#include <ANSIColors.h>
#include <json.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "WebSocketServer.h"
#include "WebConnection.h"
#include "UserInterfaceServer.h"
#include "main.h"
#include "WebSocketHTTPConfig.h"
#include "NetworkMonitorServer.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/
#define WEBSOCKET_SERVER_MAX_ADDRESS_TRIES      30
#define WEBSOCKET_SERVER_ADDRESS_WAIT_PERIOD    2

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
static pthread_t
WebSocketServerID;

static WebConnectionList*
WebSocketConnections;

static struct mg_serve_http_opts
WebSocketServerOptions;

static struct mg_connection*
WebSocketConnection;

static struct mg_mgr
WebSocketManager;

static int
WebSocketServerPollPeriod = 20;

static time_t
WebSocketServerStartTime = 0;

static int
WebSocketPacketID = 0;

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
void*
WebSocketServerThread
(void* InParameters);

void
WebSocketServerEventHandler
(struct mg_connection* InConnection, int InEvent, void* InParameter);

void
WebSocketHandlePacket
(struct mg_connection* InConnection, string InData, int InDataSize);

void
WebSocketHandleRequest
(struct mg_connection* InConnection, json_value* InJSONDoc);

void
WebSocketHandleInit
(struct mg_connection* InConnection, json_value* InJSONDoc);

void
WebSocketServerSendResponse
(struct mg_connection * InConnection, JSONOut* InBody, json_value* InJSONDoc, string InResponseType);

void
WebSocketFrameSend
(struct mg_connection* InConnection, string InBuffer, uint16_t InBufferLen);

#include "WebSocketServer/WebSocketFrameSend.c"
#include "WebSocketServer/WebSocketHandleInit.c"
#include "WebSocketServer/WebSocketHandlePacket.c"
#include "WebSocketServer/WebSocketHandleRequest.c"
#include "WebSocketServer/WebSocketServerCreateInfoScript.c"
#include "WebSocketServer/WebSocketServerEventHandler.c"
#include "WebSocketServer/WebSocketServerGetThreadID.c"
#include "WebSocketServer/WebSocketServerInitialize.c"
#include "WebSocketServer/WebSocketServerSendResponse.c"
#include "WebSocketServer/WebSocketServerStart.c"
#include "WebSocketServer/WebSocketServerThread.c"
