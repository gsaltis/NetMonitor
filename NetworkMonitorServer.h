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
networkLogFilenameDefault;

extern string
networkLogFilename;

extern bool
networkMonitorUseLoggin;

extern string
networkMonitorInterfaceNameDefault;

extern string
networkMonitorInterfaceName;

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
string
NetworkMonitorGetLogName
();

void
NetworkMonitorSetLogName
(string InLogName);

bool
NetworkMonitorGetLogging
();

void
NetworkMonitorSetLogging
(bool InUseLogging);

bool
NetworkMonitorPacketContainsAddress
(unsigned char* InBuffer, unsigned long InAddress);

unsigned long int
NetworkMonitorGetInterfaceAddress
(string InInterfaceName);

bool
NetworkMonitorIsInterface
(string InInterfaceName);

void
NetworkMonitorListInterfaces
();

void
NetworkMonitorSetInterfaceName
(string InInterfaceName);

void
NetworkMonitorInitialize
();

pthread_t
NetworkMonitorServerGetThreadID
();

void
NetworkMonitorServerStart
();

StringList*
NetworkMonitorGetNetworkInterfaces
();

#endif // _network_monitor_server_h_
