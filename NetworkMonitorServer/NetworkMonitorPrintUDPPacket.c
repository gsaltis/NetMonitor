/*****************************************************************************!
 * Function : NetworkMonitorPrintUDPPacket
 *****************************************************************************/
void 
NetworkMonitorPrintUDPPacket
(unsigned char *Buffer , int Size)
{
    
  unsigned short iphdrlen;
    
  struct iphdr *iph = (struct iphdr *)(Buffer +  sizeof(struct ethhdr));
  iphdrlen = iph->ihl*4;
    
  struct udphdr *udph = (struct udphdr*)(Buffer + iphdrlen  + sizeof(struct ethhdr));
    
  int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof udph;
    
  fprintf(logfile , "\n\n***********************UDP Packet*************************\n");
    
  NetworkMonitorPrintIPHeader(Buffer,Size);           
    
  fprintf(logfile , "\nUDP Header\n");
  fprintf(logfile , "   |-Source Port          : %d\n" , ntohs(udph->source));
  fprintf(logfile , "   |-Destination Port     : %d\n" , ntohs(udph->dest));
  fprintf(logfile , "   |-UDP Length           : %d\n" , ntohs(udph->len));
  fprintf(logfile , "   |-UDP Checksum         : %d\n" , ntohs(udph->check));
    
  fprintf(logfile , "\n");
  Buffer += sizeof(struct ethhdr);
  fprintf(logfile , "IP Header\n");
  NetworkMonitorPrintData(Buffer , iphdrlen);
        
  fprintf(logfile , "UDP Header\n");
  NetworkMonitorPrintData(Buffer+iphdrlen , sizeof udph);
        
  fprintf(logfile , "Data Payload\n");    
    
  //Move the pointer ahead and reduce the size of string
  NetworkMonitorPrintData(Buffer + header_size , Size - header_size);
    
  fprintf(logfile , "\n###########################################################");
}


