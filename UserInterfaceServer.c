/*****************************************************************************
 * FILE NAME    : UserInterfaceServer.c
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
#include <errno.h>
#include <ctype.h>
#include <pthread.h>
#include <StringUtils.h>
#include <linenoise.h>
#include <ANSIColors.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "UserInterfaceServer.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
static pthread_t
UserInterfaceServerID;

static string
UserInterfaceCommandPrompt = "Enter Command : ";

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
static void*
UserInterfaceServerThread
(void* InParameter);

static StringList*
UserInterfaceParseCommandLine
(string InCommandLine);

static void
UserInterfaceProcessCommand
(StringList* InCommand);

static void
UserInterfaceProcessCommandQuit
(StringList* InCommand);

static void
UserInterfaceProcessCommandHelp
(StringList* InCommand);

#include "UserInterfaceServer/UserInterfaceServerGetThreadID.c"
#include "UserInterfaceServer/UserInterfaceProcessCommandQuit.c"
#include "UserInterfaceServer/UserInterfaceProcessCommandHelp.c"
#include "UserInterfaceServer/UserInterfaceProcessCommand.c"
#include "UserInterfaceServer/UserInterfaceParseCommandLine.c"
#include "UserInterfaceServer/UserInterfaceServerThread.c"
#include "UserInterfaceServer/UserInterfaceServerStart.c"
#include "UserInterfaceServer/UserInterfaceServerInitialize.c"
