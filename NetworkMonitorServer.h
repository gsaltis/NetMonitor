/*****************************************************************************
 * FILE NAME    : main.h
 * DATE         : December 11 2020
 * PROJECT      : NONE
 * COPYRIGHT    : Copyright (C) 2020 by Gregory R Saltis
 *****************************************************************************/
#ifndef _network_monitor_server_h_
#define _network_monitor_server_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <pthread.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
extern string
mainFilterAddress;

extern bool
mainMonitorInterface;

extern string
mainProgramName;

extern string
mainNewGatewayAddress;

extern string
mainNewIPAddress;

extern string
mainInterfaceName;

extern bool
mainDisplayInterfaces;

extern bool
mainSetIPAddress;

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void
NetworkMonitorInitialize
();

pthread_t
NetworkMonitorServerGetThreadID
();

void
NetworkMonitorServerStart
();

#endif // _network_monitor_server_h_
