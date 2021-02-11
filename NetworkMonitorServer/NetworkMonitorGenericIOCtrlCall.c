/*****************************************************************************!
 * Function : NetworkMonitorGenericIOCtrlCall
 *****************************************************************************/
int
NetworkMonitorGenericIOCtrlCall
(int sockfd, u_long *flags, struct ifreq *ifr)
{
  if (ioctl(sockfd, (long unsigned int)flags, &ifr) < 0) {
    fprintf(stderr, "ioctl: %s\n", (char *)flags);
    return -1;
  }
  return 1;
}
