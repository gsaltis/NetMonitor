/*****************************************************************************!
 * Function : NetworkMonitorSetIPAddress
 *****************************************************************************/
int
NetworkMonitorSetIPAddress
(char *iface_name, char *ip_addr, char *gateway_addr)
{
  if(!iface_name)
    return -1;
  struct ifreq ifr;
  struct sockaddr_in sin;
  int sockfd = NetworkMonitorCreateSocket();

  sin.sin_family = AF_INET;

  // Convert IP from numbers and dots to binary notation
  inet_aton(ip_addr,(struct in_addr*)&sin.sin_addr.s_addr);

  /* get interface name */
  strncpy(ifr.ifr_name, iface_name, IFNAMSIZ);

  /* Read interface flags */
  NetworkMonitorGenericIOCtrlCall(sockfd, (u_long *)"SIOCGIFFLAGS", &ifr);
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
    NetworkMonitorGenericIOCtrlCall(sockfd, (u_long *)"SIOCSIFFLAGS", &ifr);
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
 
