/*****************************************************************************
 * FILE NAME    : main.c
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
#include <MemoryManager.h>
#include <ANSIColors.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "main.h"
#include "mainconfig.h"
#include "HTTPServer.h"
#include "UserInterfaceServer.h"
#include "WebSocketServer.h"
#include "WebSocketHTTPConfig.h"
#include "NetworkMonitorServer.h"
#include "Log.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
static void
MainInitialize
();

void
MainDisplayHelp
();

void
MainProcessCommandLine
(int argc, char** argv);

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  MainInitialize();
  MainProcessCommandLine(argc, argv);
  HTTPServerStart();

  LogWrite("Hi Mom\n");
  pthread_join(HTTPServerGetThreadID(), NULL);
  pthread_join(UserInterfaceServerGetThreadID(), NULL);
  pthread_join(WebSocketServerGetThreadID(), NULL);
  pthread_join(NetworkMonitorServerGetThreadID(), NULL);
  return EXIT_SUCCESS;
}

#include "MainProcessCommandLine.c"
#include "MainDisplayHelp.c"
#include "MainInitialize.c"

