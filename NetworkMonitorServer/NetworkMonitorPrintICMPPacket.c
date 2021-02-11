/*****************************************************************************!
 * Function : NetworkMonitorPrintICMPPacket
 *****************************************************************************/
void
NetworkMonitorPrintICMPPacket
(unsigned char* Buffer , int Size)
{
  unsigned short iphdrlen;

  struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr));
  iphdrlen = iph->ihl * 4;
    
  struct icmphdr *icmph = (struct icmphdr *)(Buffer + iphdrlen  + sizeof(struct ethhdr));
    
  int header_size =  sizeof(struct ethhdr) + iphdrlen + sizeof icmph;
    
  fprintf(logfile , "\n\n***********************ICMP Packet*************************\n"); 

  fprintf(logfile, "Full Packet\n");
  NetworkMonitorPrintData(Buffer, Size);
  
  NetworkMonitorPrintIPHeader(Buffer , Size);
            
  fprintf(logfile , "\n");
        
  fprintf(logfile , "ICMP Header\n");
  fprintf(logfile , "   |-Type : %d",(unsigned int)(icmph->type));
            
  if((unsigned int)(icmph->type) == 11)
  {
    fprintf(logfile , "  (TTL Expired)\n");
  }
  else if((unsigned int)(icmph->type) == ICMP_ECHOREPLY)
  {
    fprintf(logfile , "  (ICMP Echo Reply)\n");
  }
    
  fprintf(logfile , "   |-Code : %d\n",(unsigned int)(icmph->code));
  fprintf(logfile , "   |-Checksum : %d\n",ntohs(icmph->checksum));
  //fprintf(logfile , "   |-ID       : %d\n",ntohs(icmph->id));
  //fprintf(logfile , "   |-Sequence : %d\n",ntohs(icmph->sequence));
  fprintf(logfile , "\n");

  Buffer += sizeof(struct ethhdr);
  
  fprintf(logfile , "IP Header\n");
  NetworkMonitorPrintData(Buffer,iphdrlen);
        
  fprintf(logfile , "UDP Header\n");
  NetworkMonitorPrintData(Buffer + iphdrlen , sizeof icmph);
        
  fprintf(logfile , "Data Payload\n");    
    
  //Move the pointer ahead and reduce the size of string
  NetworkMonitorPrintData(Buffer + header_size , (Size - header_size) );
    
  fprintf(logfile , "\n###########################################################");
}


