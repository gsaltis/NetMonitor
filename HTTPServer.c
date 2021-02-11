/*****************************************************************************
 * FILE NAME    : HTTPServer.c
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
#include <ANSIColors.h>
#include <mongoose.h>
#include <StringUtils.h>
#include <MemoryManager.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "HTTPServer.h"
#include "WebSocketServer.h"
#include "WebSocketHTTPConfig.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
static pthread_t
HTTPServerThreadID;

static int
HTTPServerPollPeriod = 20;

static struct mg_serve_http_opts
HTTPServerOptions;

static struct mg_connection*
HTTPConnection;

static struct mg_mgr
HTTPManager;

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
void*
HTTPServerThread
(void* InParameters);

void
HTTPServerEventHandler
(struct mg_connection* InConnection, int InEvent, void* InParameter);


#include "HTTPServer/HTTPServerGetThreadID.c"
#include "HTTPServer/HTTPServerEventHandler.c"
#include "HTTPServer/HTTPServerThread.c"
#include "HTTPServer/HTTPServerStart.c"
#include "HTTPServer/HTTPServerInitialize.c"
