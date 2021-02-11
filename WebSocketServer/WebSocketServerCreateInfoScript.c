/*****************************************************************************!
 * Function : WebSocketServerCreateInfoScript
 *****************************************************************************/
void
WebSocketServerCreateInfoScript
()
{
  struct ifaddrs*                       addresses;
  struct ifaddrs*                       tempAddress;
  
  string                                address;
  int                                   fd;
  struct                                ifreq ifr;
  FILE*                                 file;
  struct sockaddr_in*                   sa;
  char                                  b;
  bool                                  found;
  string                                interface;

  found = false;

  getifaddrs(&addresses);
  
  printf("%sWebSocket Script         : ", ColorGreen);
  fflush(stdout);
  //! We only want to do this when we have a value 192. address
  //  So we loop until we do or we eventually give up
  for (int i = 0; i < WEBSOCKET_SERVER_MAX_ADDRESS_TRIES && !found; i++ ) { 
    for ( tempAddress = addresses ; tempAddress ; tempAddress = tempAddress->ifa_next ) {
      if ( ! (tempAddress->ifa_addr && tempAddress->ifa_addr->sa_family == AF_PACKET) ) {
        continue;
      }
      fd = socket(AF_INET, SOCK_DGRAM, 0);
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
        file = fopen("www/websocketinfo.js", "wb");
        if ( NULL == file ) {
          return;
        }
        fprintf(file, "var WebSocketIFAddress = \"%s\";\n", address);
        fprintf(file, "var WebSocketIFPort = \"%s\";\n", WebSocketHTTPGetWebSocketHTTPPortAddress());
        fclose(file);
        FreeMemory(address);
        found = true;
      }
      if ( !found ) {
        //! We don't so sleep and try again
        sleep(WEBSOCKET_SERVER_ADDRESS_WAIT_PERIOD);
      }
    }
  }
  freeifaddrs(addresses);
  printf("%s%screated%s\n", ColorYellow, found ? "" : "not ", ColorReset);
}



