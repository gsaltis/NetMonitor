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

#include <ANSIColors.h>
#include <StringUtils.h>
#include <MemoryManager.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "main.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/
static string
mainFilterAddress = NULL;

static bool
mainMonitorInterface = false;

static string
mainProgramName = "netmon";

static string
mainNewGatewayAddress = NULL;

static string
mainNewIPAddress = NULL;

static string
mainInterfaceName = NULL;

static bool
mainDisplayInterfaces = false;

static bool
mainSetIPAddress = false;

static FILE*
logfile;

static int
tcp=0,udp=0,icmp=0,others=0,igmp=0,total=0; 

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
void
MainDisplayHelp
();

void
MainProcessCommandLine
(int argc, char** argv);

void
MainInitialize
();

void
MainGetNetworkInterfaces
();

int
MainSetIPAddress
(char *iface_name, char *ip_addr, char *gateway_addr);

void
ProcessPacket
(unsigned char* , int);

void
MainPrintIPHeader
(unsigned char* , int);

void
MainPrintTCPPacket
(unsigned char * , int);

void
MainPrintUDPPacket
(unsigned char * , int);

void
MainPrintICMPPacket
(unsigned char* , int);

void
PrintData 
(unsigned char* , int);

void
MainMonitorInterface
();

void
MainPrintEthernetHeader
(unsigned char* Buffer, int Size);

/*****************************************************************************!
 * Function : main
 *****************************************************************************/
int
main
(int argc, char** argv)
{
  MainInitialize();
  MainProcessCommandLine(argc, argv);
  if ( mainDisplayInterfaces ) {
    MainGetNetworkInterfaces();
  }
  if ( mainSetIPAddress ) {
    MainSetIPAddress(mainInterfaceName, mainNewIPAddress, mainNewGatewayAddress);
  }
  if ( mainMonitorInterface ) {
    MainMonitorInterface();
  }
  if ( !mainDisplayInterfaces && ! mainSetIPAddress && !mainMonitorInterface ) {
    MainDisplayHelp();
  }
  return EXIT_SUCCESS;
}

/*****************************************************************************!
 * Function : MainGetNetworkInterfaces
 *****************************************************************************/
void
MainGetNetworkInterfaces
()
{
  struct ifaddrs*                       addresses;
  struct ifaddrs*                       tempAddress;
  string                                address;
  int                                   fd;
  struct ifreq                          ifr;
  struct sockaddr_in*                   sa;
  char                                  b;
  string                                interface;
  
  getifaddrs(&addresses);
  fflush(stdout);
  //! We only want to do this when we have a value 192. address
  //  So we loop until we do or we eventually give up
  for ( tempAddress = addresses ; tempAddress ; tempAddress = tempAddress->ifa_next ) {
    if ( ! (tempAddress->ifa_addr && tempAddress->ifa_addr->sa_family == AF_PACKET) ) {
      continue;
    }
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    fflush(stdout); 
    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;
    
    interface = tempAddress->ifa_name;    
    strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);
    
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    sa = (struct sockaddr_in*)&ifr.ifr_addr;
    b = (char)(sa->sin_addr.s_addr & 0xFF);
    
    //! Check that we have a at least a C Address
    if ( b & 0xC0 ) {
      address = StringCopy(inet_ntoa(sa->sin_addr));
      printf("Address = %-8s %s\n", interface, address);
      FreeMemory(address);
    }
  }
  freeifaddrs(addresses);

}

/*****************************************************************************!
 * Function : MainCreateSocket
 *****************************************************************************/
int MainCreateSocket() {

  int sockfd = 0;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd == -1){
    fprintf(stderr, "Could not get socket.\n");
    return -1;
  }

  return sockfd;
}

/*****************************************************************************!
 * Function : generic_ioctrlcall
 *****************************************************************************/
int generic_ioctrlcall(int sockfd, u_long *flags, struct ifreq *ifr) {

  if (ioctl(sockfd, (long unsigned int)flags, &ifr) < 0) {
    fprintf(stderr, "ioctl: %s\n", (char *)flags);
    return -1;
  }
  return 1;
}

/*****************************************************************************!
 * Function : set_route
 *****************************************************************************/
int set_route(int sockfd, char *gateway_addr,  struct sockaddr_in *addr) {
  struct rtentry route;
  int err = 0;
  memset(&route, 0, sizeof(route));
  addr = (struct sockaddr_in*) &route.rt_gateway;
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr(gateway_addr);
  addr = (struct sockaddr_in*) &route.rt_dst;
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr("0.0.0.0");
  addr = (struct sockaddr_in*) &route.rt_genmask;
  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr("0.0.0.0");
  route.rt_flags = RTF_UP | RTF_GATEWAY;
  route.rt_metric = 100;
  err = ioctl(sockfd, SIOCADDRT, &route);
  if ((err) < 0) {
    fprintf(stderr, "ioctl: %s : %s\n",  "mahdi MOAHMMADI Error ", strerror(errno));
    return -1;
  }
  return 1;
}

/*****************************************************************************!
 * Function : MainSetIPAddress
 *****************************************************************************/
int
MainSetIPAddress
(char *iface_name, char *ip_addr, char *gateway_addr)
{
  if(!iface_name)
    return -1;
  struct ifreq ifr;
  struct sockaddr_in sin;
  int sockfd = MainCreateSocket();

  sin.sin_family = AF_INET;

  // Convert IP from numbers and dots to binary notation
  inet_aton(ip_addr,(struct in_addr*)&sin.sin_addr.s_addr);

  /* get interface name */
  strncpy(ifr.ifr_name, iface_name, IFNAMSIZ);

  /* Read interface flags */
  generic_ioctrlcall(sockfd, (u_long *)"SIOCGIFFLAGS", &ifr);
  /*
   * Expected in <net/if.h> according to
   * "UNIX Network Programming".
   */
#ifdef ifr_flags
# define IRFFLAGS       ifr_flags
#else   /* Present on kFreeBSD */
# define IRFFLAGS       ifr_flagshigh
#endif
  // If interface is down, bring it up
  if (ifr.IRFFLAGS | ~(IFF_UP)) {
    ifr.IRFFLAGS |= IFF_UP;
    generic_ioctrlcall(sockfd, (u_long *)"SIOCSIFFLAGS", &ifr);
  }
  // Set route
  // set_route(sockfd, gateway_addr    ,  &sin);
  memcpy(&ifr.ifr_addr, &sin, sizeof(struct sockaddr)); 
  // Set interface address
  if (ioctl(sockfd, SIOCSIFADDR, &ifr) < 0) {
    fprintf(stderr, "Cannot set IP address. ");
    perror(ifr.ifr_name);
    return -1;
  }             
#undef IRFFLAGS 

  return 0;
}
 

/*****************************************************************************!
 * Function : MainInitialize
 *****************************************************************************/
void
MainInitialize
()
{
  mainSetIPAddress = false;
  mainDisplayInterfaces = false;
}

/*****************************************************************************!
 * Function : MainProcessCommandLine
 *****************************************************************************/
void
MainProcessCommandLine
(int argc, char** argv)
{
  StringList*                           s2;
  string                                s;
  int                                   n;
  int                                   i;
  string                                command;

  for (i = 1; i < argc; i++) {
    command = argv[i];
    if ( StringEqualsOneOf(command, "-h", "--help", NULL) ) {
      MainDisplayHelp();
      exit(EXIT_SUCCESS);
    }
    if ( StringEqualsOneOf(command, "-d", "--display", NULL) ) {
      mainDisplayInterfaces = true;
      continue;
    }
    if ( StringEqualsOneOf(command, "-m", "--monitor", NULL) ) {
      mainMonitorInterface = true;
      n = i +1;
      if ( argc == n ) {
        continue;
      }
      if ( StringBeginsWith(argv[n], "-") ) {
        continue;
      }
      if ( mainFilterAddress ) {
        FreeMemory(mainFilterAddress);
      }
      mainFilterAddress = StringCopy(argv[n]);
      i++;
      continue;
    }
    if ( StringEqualsOneOf(command, "-a", "--address", NULL) ) {
      if ( i + 2 >= argc ) {
        fprintf(stderr, "%s\"%s\" requires an interface name and an IP address%s\n",
                ColorBrightRed, command, ColorReset);
        MainDisplayHelp();
        exit(EXIT_FAILURE);
      }
      i++;
      mainInterfaceName = StringCopy(argv[i]);
      i++;
      mainNewIPAddress = StringCopy(argv[i]);
      n = i + 1;
      if ( n + 1 < argc ) {
        s = argv[n];
        if ( StringBeginsWith(s, "-") ) {
          continue;
        }
        i++;
        mainNewGatewayAddress = StringCopy(argv[i]);
      } else {
        s2 = StringSplit(mainNewIPAddress, ".", false);
        if ( NULL == s2 || s2->stringCount != 4 ) {
          fprintf(stderr, "%s\"%s\" does not appear to be valid IP4 address%s\n",
                  ColorBrightRed, mainNewIPAddress, ColorReset);
          MainDisplayHelp();
          exit(EXIT_FAILURE);
        } else {
          mainNewGatewayAddress = StringMultiConcat(s2->strings[0], ".",
                                                    s2->strings[1], ".",
                                                    s2->strings[2], ".",
                                                    "1",
                                                    NULL);
        }
        StringListDestroy(s2);
      }
      mainSetIPAddress = true;
      continue;
    }
    fprintf(stderr, "%s\"%s\" is not a valid command%s\n", ColorBrightRed, command, ColorReset);
    MainDisplayHelp();
    exit(EXIT_FAILURE);
  }
}

/*****************************************************************************!
 * Function : MainDisplayHelp
 *****************************************************************************/
void
MainDisplayHelp
()
{
  printf("Usage %s options\n", mainProgramName);
  printf("OPTIONS\n");
  printf("  -h, --help                                             : Display this information\n");
  printf("  -a, --address <interface> <ipaddress> {gatewayaddress} : Set the interfaces IP4 address and optionally the gateway address\n");
  printf("  -d, --display                                          : Display the interface information\n");
  printf("  -m {ipaddress}                                         : Monitor a network interface\n");
}


/*****************************************************************************!
 * Function : MainMonitorInterface
 *****************************************************************************/
void
MainMonitorInterface
()
{
  int saddr_size , data_size;
  struct sockaddr saddr;
  
  unsigned char *buffer = (unsigned char *) malloc(65536); //Its Big!
    
  logfile=fopen("log.txt","w");
  if(logfile==NULL) 
  {
    printf("Unable to create log.txt file.");
  }
  printf("Starting...\n");
    
  int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
  setsockopt(sock_raw , SOL_SOCKET , SO_BINDTODEVICE , "eth0" , strlen("eth0")+ 1 );
    
  if(sock_raw < 0)
  {
    //Print the error with proper message
    perror("Socket Error");
    return;
  }
  while(1)
  {
    saddr_size = sizeof saddr;
    //Receive a packet
    data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , (socklen_t*)&saddr_size);
    if(data_size <0 )
    {
      printf("Recvfrom error , failed to get packets\n");
      return ;
    }
    //Now process the packet
    ProcessPacket(buffer , data_size);
  }
  close(sock_raw);
  printf("Finished");
  return;
}

/*****************************************************************************!
 * Function : ProcessPacket
 *****************************************************************************/
void ProcessPacket(unsigned char* buffer, int size)
{
  string                                saddr;
  string                                daddr;
  struct sockaddr_in                    source,dest;

  //Get the IP Header part of this packet , excluding the ethernet header
  struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
  ++total;

  memset(&source, 0, sizeof(source));
  source.sin_addr.s_addr = iph->saddr;
    
  memset(&dest, 0, sizeof(dest));
  dest.sin_addr.s_addr = iph->daddr;

  saddr = StringCopy(inet_ntoa(source.sin_addr));
  daddr = StringCopy(inet_ntoa(dest.sin_addr));

  if ( mainFilterAddress ) {
    if ( !StringEqual(saddr, mainFilterAddress) && !StringEqual(daddr, mainFilterAddress) ) {
      FreeMemory(saddr);
      FreeMemory(daddr);
      return;
    }
  }
  switch (iph->protocol) //Check the Protocol and do accordingly...
  {
    case 1:  //ICMP Protocol
      ++icmp;
      MainPrintICMPPacket( buffer , size);
      break;
        
    case 2:  //IGMP Protocol
      ++igmp;
      break;
        
    case 6:  //TCP Protocol
      ++tcp;
      MainPrintTCPPacket(buffer , size);
      break;
        
    case 17: //UDP Protocol
      ++udp;
      MainPrintUDPPacket(buffer , size);
      break;
        
    default: //Some Other Protocol like ARP etc.
      ++others;
      break;
  }
  printf("TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\r",
         tcp , udp , icmp , igmp , others , total);
  fflush(stdout);
  FreeMemory(saddr);
  FreeMemory(daddr);
}

/*****************************************************************************!
 * Function : MainPrintEthernetHeader
 *****************************************************************************/
void
 MainPrintEthernetHeader
(unsigned char* Buffer, int Size)
{
  struct ethhdr *eth = (struct ethhdr *)Buffer;
    
  fprintf(logfile , "\n");
  fprintf(logfile , "Ethernet Header\n");
  fprintf(logfile , "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
  fprintf(logfile , "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
  fprintf(logfile , "   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
}

/*****************************************************************************!
 * Function : MainPrintIPHeader
 *****************************************************************************/
void
MainPrintIPHeader
(unsigned char* Buffer, int Size)
{
  struct sockaddr_in                    source,dest;
  
  MainPrintEthernetHeader(Buffer , Size);
        
  struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    
  memset(&source, 0, sizeof(source));
  source.sin_addr.s_addr = iph->saddr;
    
  memset(&dest, 0, sizeof(dest));
  dest.sin_addr.s_addr = iph->daddr;
    
  fprintf(logfile , "\n");
  fprintf(logfile , "IP Header\n");
  fprintf(logfile , "   |-IP Version           : %d\n",(unsigned int)iph->version);
  fprintf(logfile , "   |-IP Header Length     : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
  fprintf(logfile , "   |-Type Of Service      : %d\n",(unsigned int)iph->tos);
  fprintf(logfile , "   |-IP Total Length      : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
  fprintf(logfile , "   |-Identification       : %d\n",ntohs(iph->id));
  //fprintf(logfile , "   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
  //fprintf(logfile , "   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
  //fprintf(logfile , "   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
  fprintf(logfile , "   |-TTL                  : %d\n",(unsigned int)iph->ttl);
  fprintf(logfile , "   |-Protocol             : %d\n",(unsigned int)iph->protocol);
  fprintf(logfile , "   |-Checksum             : %d\n",ntohs(iph->check));
  fprintf(logfile , "   |-Source IP            : %s\n",inet_ntoa(source.sin_addr));
  fprintf(logfile , "   |-Destination IP       : %s\n",inet_ntoa(dest.sin_addr));
}

/*****************************************************************************!
 * Function : MainPrintTCPPacket
 *****************************************************************************/
void
MainPrintTCPPacket
(unsigned char* Buffer, int Size)
{
  unsigned short iphdrlen;
    
  struct iphdr *iph = (struct iphdr *)( Buffer  + sizeof(struct ethhdr) );
  iphdrlen = iph->ihl*4;
    
  struct tcphdr *tcph=(struct tcphdr*)(Buffer + iphdrlen + sizeof(struct ethhdr));
            
  int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;
    
  fprintf(logfile , "\n\n***********************TCP Packet*************************\n");  
        
  MainPrintIPHeader(Buffer,Size);
        
  fprintf(logfile , "\n");
  fprintf(logfile , "TCP Header\n");
  fprintf(logfile , "   |-Source Port          : %u\n",ntohs(tcph->source));
  fprintf(logfile , "   |-Destination Port     : %u\n",ntohs(tcph->dest));
  fprintf(logfile , "   |-Sequence Number      : %u\n",ntohl(tcph->seq));
  fprintf(logfile , "   |-Acknowledge Number   : %u\n",ntohl(tcph->ack_seq));
  fprintf(logfile , "   |-Header Length        : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
  //fprintf(logfile , "   |-CWR Flag : %d\n",(unsigned int)tcph->cwr);
  //fprintf(logfile , "   |-ECN Flag : %d\n",(unsigned int)tcph->ece);
  fprintf(logfile , "   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
  fprintf(logfile , "   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
  fprintf(logfile , "   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
  fprintf(logfile , "   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
  fprintf(logfile , "   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
  fprintf(logfile , "   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
  fprintf(logfile , "   |-Window               : %d\n",ntohs(tcph->window));
  fprintf(logfile , "   |-Checksum             : %d\n",ntohs(tcph->check));
  fprintf(logfile , "   |-Urgent Pointer       : %d\n",tcph->urg_ptr);
  fprintf(logfile , "\n");
  fprintf(logfile , "                        DATA Dump                         ");
  fprintf(logfile , "\n");
        
  Buffer += sizeof(struct ethhdr);
  fprintf(logfile , "IP Header\n");
  PrintData(Buffer,iphdrlen);
        
  fprintf(logfile , "TCP Header\n");
  PrintData(Buffer+iphdrlen,tcph->doff*4);
        
  fprintf(logfile , "Data Payload\n");    
  PrintData(Buffer + header_size , Size - header_size );
                        
  fprintf(logfile , "\n###########################################################");
}

/*****************************************************************************!
 * Function : MainPrintUDPPacket
 *****************************************************************************/
void MainPrintUDPPacket(unsigned char *Buffer , int Size)
{
    
  unsigned short iphdrlen;
    
  struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
  iphdrlen = iph->ihl*4;
    
  struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
    
  int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
    
  fprintf(logfile , "\n\n***********************UDP Packet*************************\n");
    
  MainPrintIPHeader(Buffer,Size);           
    
  fprintf(logfile , "\nUDP Header\n");
  fprintf(logfile , "   |-Source Port          : %d\n" , ntohs(udph->source));
  fprintf(logfile , "   |-Destination Port     : %d\n" , ntohs(udph->dest));
  fprintf(logfile , "   |-UDP Length           : %d\n" , ntohs(udph->len));
  fprintf(logfile , "   |-UDP Checksum         : %d\n" , ntohs(udph->check));
    
  fprintf(logfile , "\n");
  Buffer += sizeof(struct ethhdr);
  fprintf(logfile , "IP Header\n");
  PrintData(Buffer , iphdrlen);
        
  fprintf(logfile , "UDP Header\n");
  PrintData(Buffer+iphdrlen , sizeof udph);
        
  fprintf(logfile , "Data Payload\n");    
    
  //Move the pointer ahead and reduce the size of string
  PrintData(Buffer + header_size , Size - header_size);
    
  fprintf(logfile , "\n###########################################################");
}

/*****************************************************************************!
 * Function : MainPrintICMPPacket
 *****************************************************************************/
void
MainPrintICMPPacket
(unsigned char* Buffer , int Size)
{
  unsigned short iphdrlen;

  struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr));
  iphdrlen = iph->ihl * 4;
    
  struct icmphdr *icmph = (struct icmphdr *)(Buffer + iphdrlen  + sizeof(struct ethhdr));
    
  int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof icmph;
    
  fprintf(logfile , "\n\n***********************ICMP Packet*************************\n"); 

  fprintf(logfile, "Full Packet\n");
  PrintData(Buffer, Size);
  
  MainPrintIPHeader(Buffer , Size);
            
  fprintf(logfile , "\n");
        
  fprintf(logfile , "ICMP Header\n");
  fprintf(logfile , "   |-Type : %d",(unsigned int)(icmph->type));
            
  if((unsigned int)(icmph->type) == 11)
  {
    fprintf(logfile , "  (TTL Expired)\n");
  }
  else if((unsigned int)(icmph->type) == ICMP_ECHOREPLY)
  {
    fprintf(logfile , "  (ICMP Echo Reply)\n");
  }
    
  fprintf(logfile , "   |-Code : %d\n",(unsigned int)(icmph->code));
  fprintf(logfile , "   |-Checksum : %d\n",ntohs(icmph->checksum));
  //fprintf(logfile , "   |-ID       : %d\n",ntohs(icmph->id));
  //fprintf(logfile , "   |-Sequence : %d\n",ntohs(icmph->sequence));
  fprintf(logfile , "\n");

  Buffer += sizeof(struct ethhdr);
  
  fprintf(logfile , "IP Header\n");
  PrintData(Buffer,iphdrlen);
        
  fprintf(logfile , "UDP Header\n");
  PrintData(Buffer + iphdrlen , sizeof icmph);
        
  fprintf(logfile , "Data Payload\n");    
    
  //Move the pointer ahead and reduce the size of string
  PrintData(Buffer + header_size , (Size - header_size) );
    
  fprintf(logfile , "\n###########################################################");
}

/*****************************************************************************!
 * Function : PrintData
 *****************************************************************************/
void
PrintData
(unsigned char* data , int Size)
{
  int i , j;
  for(i=0 ; i < Size ; i++)
  {
    if( i!=0 && i%16==0)   //if one line of hex printing is complete...
    {
      fprintf(logfile , "         ");
      for(j=i-16 ; j<i ; j++)
      {
        if(data[j]>=32 && data[j]<=128)
          fprintf(logfile , "%c",(unsigned char)data[j]); //if its a number or alphabet
                
        else fprintf(logfile , "."); //otherwise print a dot
      }
      fprintf(logfile , "\n");
    } 
        
    if(i%16==0) fprintf(logfile , "   ");
    fprintf(logfile , " %02X",(unsigned int)data[i]);
                
    if( i==Size-1)  //print the last spaces
    {
      for(j=0;j<15-i%16;j++) 
      {
        fprintf(logfile , "   "); //extra spaces
      }
            
      fprintf(logfile , "         ");
            
      for(j=i-i%16 ; j<=i ; j++)
      {
        if(data[j]>=32 && data[j]<=128) 
        {
          fprintf(logfile , "%c",(unsigned char)data[j]);
        }
        else 
        {
          fprintf(logfile , ".");
        }
      }
            
      fprintf(logfile ,  "\n" );
    }
  }
}
