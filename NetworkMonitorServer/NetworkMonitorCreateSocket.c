/*****************************************************************************!
 * Function : NetworkMonitorCreateSocket
 *****************************************************************************/
int
NetworkMonitorCreateSocket
()
{
  int sockfd = 0;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd == -1){
    fprintf(stderr, "Could not get socket.\n");
    return -1;
  }

  return sockfd;
}

