/*****************************************************************************!
 * Function : NetworkMonitorInterface
 *****************************************************************************/
void
NetworkMonitorInterface
()
{
  unsigned int long                     ipaddress, lastIPAddress;
  int                                   rvalue;
  int                                   saddr_size , data_size;
  struct sockaddr                       saddr;
  fd_set                                readfds, exceptfds;
  struct timeval                        tv;
  
  unsigned char *                       buffer = (unsigned char *) malloc(65536); //Its Big!
    
  logfile=fopen(networkLogFilename,"w");
  if(logfile==NULL) 
  {
    printf("Unable to create log.txt file.");
  }
  printf("Starting...\n");
    
  int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
  setsockopt(sock_raw , SOL_SOCKET , SO_BINDTODEVICE , networkMonitorInterfaceName , strlen(networkMonitorInterfaceName)+ 1 );
  if(sock_raw < 0)
  {
    //Print the error with proper message
    perror("Socket Error");
    return;
  }

  ipaddress = NetworkMonitorGetInterfaceAddress(networkMonitorInterfaceName);
  lastIPAddress = ipaddress;
  while(1)
  {
    saddr_size = sizeof saddr;
    FD_ZERO(&readfds);
    FD_SET(sock_raw, &readfds);
    FD_SET(sock_raw, &exceptfds);
    tv.tv_usec = 0;
    tv.tv_sec = 5;

    ipaddress = NetworkMonitorGetInterfaceAddress(networkMonitorInterfaceName);
    
    if ( lastIPAddress != ipaddress ) {
      lastIPAddress = ipaddress;
      printf("%s %d : %08x %08x\n", __FILE__, __LINE__, ipaddress, lastIPAddress);
    }
    if ( ipaddress == 0 ) {
      continue;
    }
    rvalue = select(sock_raw+1, &readfds, NULL, &exceptfds, &tv);

    //Receive a packet

    if ( rvalue == 0  ) {
      // Timer timeout;
      continue;
    }
    if ( rvalue == -1 ) {
      perror("Read Error");
      continue;
    }

    if ( FD_ISSET(sock_raw, &readfds) ) {
      data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , (socklen_t*)&saddr_size);
      if(data_size < 0 )
      {
        printf("Recvfrom error , failed to get packets\n");
        return ;
      }

      if ( data_size == 0 ) {
        printf("%s disconnected\n", networkMonitorInterfaceName);
        continue;
      }
      if ( NetworkMonitorPacketContainsAddress(buffer, ipaddress) ) {
        NetworkMonitorProcessPacket(buffer , data_size);
      }
      continue;
    }

    if ( FD_ISSET(sock_raw, &exceptfds) ) {
      printf("%s %d : Socket exception\n", __FILE__, __LINE__);
      continue;
    }
  }
  close(sock_raw);
  printf("Finished");
  return;
}


