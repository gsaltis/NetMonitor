/*****************************************************************************
 * FILE NAME    : WebSocketHTTPConfig.c
 * DATE         : January 11 2021
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2021 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <StringUtils.h>
#include <MemoryManager.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "WebSocketHTTPConfig.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
static string
WWWDirectoryDefault = "www";

static string
WWWDirectory = NULL;

static string
WebSocketPortAddressDefault = "8002";

static string
WebSocketPortAddress = NULL;

static string
HTTPPortAddress = NULL;

static string
HTTPPortAddressDefault = "8001";

#include "WebSocketHTTPConfig/WebSocketHTTPInitialize.c"
#include "WebSocketHTTPConfig/WebSocketHTTPGetWWWDirectory.c"
#include "WebSocketHTTPConfig/WebSocketHTTPGetHTTPPortAddress.c"
#include "WebSocketHTTPConfig/WebSocketHTTPGetWebSocketHTTPPortAddress.c"
#include "WebSocketHTTPConfig/WebSocketHTTPSetWWWDirectory.c"
#include "WebSocketHTTPConfig/WebSocketHTTPSetHTTPPortAddress.c"
#include "WebSocketHTTPConfig/WebSocketHTTPSetWebSocketPortAddress.c"
