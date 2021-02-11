/*****************************************************************************!
 * Function : NetworkMonitorGetInterfaceAddress
 *****************************************************************************/
unsigned long int
NetworkMonitorGetInterfaceAddress
(string InInterfaceName)
{
  int fd;
  struct ifreq ifr;

  fd = socket(AF_INET, SOCK_DGRAM, 0);

  ifr.ifr_addr.sa_family = AF_INET;
  strncpy(ifr.ifr_name, InInterfaceName, IFNAMSIZ-1);

  ioctl(fd, SIOCGIFADDR, &ifr);
  close(fd);

  return (unsigned long int)((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr;
}
