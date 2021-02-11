/*****************************************************************************!
 * Function : NetworkMonitorInterface
 *****************************************************************************/
void
NetworkMonitorInterface
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
    NetworkMonitorProcessPacket(buffer , data_size);
  }
  close(sock_raw);
  printf("Finished");
  return;
}


