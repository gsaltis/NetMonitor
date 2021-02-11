/*****************************************************************************!
 * Function : NetworkMonitorGetNetworkInterfaces
 *****************************************************************************/
StringList*
NetworkMonitorGetNetworkInterfaces
()
{
  struct ifaddrs*                       addresses;
  struct ifaddrs*                       tempAddress;
  string                                address;
  int                                   fd;
  struct ifreq                          ifr;
  struct sockaddr_in*                   sa;
  string                                interface;
  StringList*                           interfaces;

  interfaces = StringListCreate();
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

    address = StringCopy(inet_ntoa(sa->sin_addr));
    StringListAppend(interfaces, StringCopy(interface));
    FreeMemory(address);
  }
  freeifaddrs(addresses);
  return interfaces;
}


