/*****************************************************************************
 * FILE NAME    : main.c
 * DATE         : December 11 2020
 * PROJECT      : NONE
 * COPYRIGHT    : Copyright (C) 2020 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <arpa/inet.h>
#include <errno.h>
#include <ifaddrs.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <net/route.h>
#include <netdb.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include <ANSIColors.h>
#include <StringUtils.h>
#include <MemoryManager.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "NetworkMonitorServer.h"
#include "UserInterfaceServer.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
string
networkLogFilenameDefault = "log.txt";

string
networkLogFilename;

bool
networkMonitorUseLogging = false;

string
networkMonitorInterfaceNameDefault = "eth0";

string
networkMonitorInterfaceName;

string
mainFilterAddress = NULL;

bool
mainMonitorInterface = false;

string
mainProgramName = "netmon";

string
mainNewGatewayAddress = NULL;

string
mainNewIPAddress = NULL;

string
mainInterfaceName = NULL;

bool
mainDisplayInterfaces = false;

bool
mainSetIPAddress = false;

FILE*
logfile;

static int
tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0;

pthread_t
networkMonitorServerID;

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
void
MainGetNetworkInterfaces
();

int
NetworkMonitorSetIPAddress
(char *iface_name, char *ip_addr, char *gateway_addr);

void
NetworkMonitorProcessPacket
(unsigned char* , int);

void
NetworkMonitorPrintIPHeader
(unsigned char* , int);

void
NetworkMonitorPrintTCPPacket
(unsigned char * , int);

void
NetworkMonitorPrintUDPPacket
(unsigned char * , int);

void
NetworkMonitorPrintICMPPacket
(unsigned char* , int);

void
NetworkMonitorPrintData
(unsigned char* , int);

void
NetworkMonitorInterface
();

void
NetworkMonitorPrintEthernetHeader
(unsigned char* Buffer, int Size);

void*
NetworkMonitorServerThread
(void* InParameters);

int
NetworkMonitorGenericIOCtrlCall
(int sockfd, u_long *flags, struct ifreq *ifr);

int
NetworkMonitorCreateSocket
();

#if 0
/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  MainProcessCommandLine(argc, argv);
  if ( mainDisplayInterfaces ) {
    MainGetNetworkInterfaces();
  }
  if ( mainSetIPAddress ) {
    NetworkMonitorSetIPAddress(mainInterfaceName, mainNewIPAddress, mainNewGatewayAddress);
  }
  if ( mainMonitorInterface ) {
    MainMonitorInterface();
  }
  if ( !mainDisplayInterfaces && ! mainSetIPAddress && !mainMonitorInterface ) {
    MainDisplayHelp();
  }
  return EXIT_SUCCESS;
}
#endif


#include "NetworkMonitorServer/NetworkMonitorServerGetThreadID.c"
#include "NetworkMonitorServer/NetworkMonitorServerThread.c"
#include "NetworkMonitorServer/NetworkMonitorServerStart.c"
#include "NetworkMonitorServer/NetworkMonitorInitialize.c"
#include "NetworkMonitorServer/NetworkMonitorPrintData.c"
#include "NetworkMonitorServer/NetworkMonitorPrintICMPPacket.c"
#include "NetworkMonitorServer/NetworkMonitorPrintUDPPacket.c"
#include "NetworkMonitorServer/NetworkMonitorPrintTCPPacket.c"
#include "NetworkMonitorServer/NetworkMonitorPrintIPHeader.c"
#include "NetworkMonitorServer/NetworkMonitorPrintEthernetHeader.c"
#include "NetworkMonitorServer/NetworkMonitorProcessPacket.c"
#include "NetworkMonitorServer/NetworkMonitorInterface.c"
#include "NetworkMonitorServer/NetworkMonitorSetIPAddress.c"
#include "NetworkMonitorServer/NetworkMonitorSetRoute.c"
#include "NetworkMonitorServer/NetworkMonitorGenericIOCtrlCall.c"
#include "NetworkMonitorServer/NetworkMonitorGetNetworkInterfaces.c"
#include "NetworkMonitorServer/NetworkMonitorCreateSocket.c"
#include "NetworkMonitorServer/NetworkMonitorSetInterfaceName.c"
#include "NetworkMonitorServer/NetworkMonitorListInterfaces.c"
#include "NetworkMonitorServer/NetworkMonitorIsInterface.c"
#include "NetworkMonitorServer/NetworkMonitorGetInterfaceAddress.c"
#include "NetworkMonitorServer/NetworkMonitorPacketContainsAddress.c"
#include "NetworkMonitorServer/NetworkMonitorSetLogging.c"
#include "NetworkMonitorServer/NetworkMonitorGetLogging.c"
#include "NetworkMonitorServer/NetworkMonitorSetLogName.c"
#include "NetworkMonitorServer/NetworkMonitorGetLogName.c"
