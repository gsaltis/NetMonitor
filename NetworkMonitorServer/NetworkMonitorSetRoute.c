/*****************************************************************************!
 * Function : NetworkMonitorSetRoute
 *****************************************************************************/
int 
NetworkMonitorSetRoute
(int sockfd, char *gateway_addr,  struct sockaddr_in *addr) {
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

