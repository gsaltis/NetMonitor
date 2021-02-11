/*****************************************************************************
 * FILE NAME    : WebConnection.c
 * DATE         : April 22 2020 
 * PROJECT      : BDBF Simulator
 * COPYRIGHT    : Copyright (C) 2020 by Vertiv Company
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <MemoryManager.h>
#include <StringUtils.h>
#include <mongoose.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "WebConnection.h"
#include "WebSocketHTTPConfig.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/

#include "WebConnection/WebConnectionTimeUpdate.c"
#include "WebConnection/WebConnectionListGetByIndex.c" 
#include "WebConnection/WebConnectionListDisplay.c"
#include "WebConnection/WebConnectionListCount.c"
#include "WebConnection/WebConnectionListFind.c"
#include "WebConnection/WebConnectionListRemove.c"
#include "WebConnection/WebConnectionListAppend.c"
#include "WebConnection/WebConnectionListCreate.c"
#include "WebConnection/WebConnectionClose.c"
#include "WebConnection/WebConnectionDestroy.c"
#include "WebConnection/WebConnectionCreate.c"
