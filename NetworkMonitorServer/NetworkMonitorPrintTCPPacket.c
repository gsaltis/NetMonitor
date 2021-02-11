/*****************************************************************************!
 * Function : NetworkMonitorPrintTCPPacket
 *****************************************************************************/
void
NetworkMonitorPrintTCPPacket
(unsigned char* Buffer, int Size)
{
  unsigned short iphdrlen;
    
  struct iphdr *iph = (struct iphdr *)( Buffer  + sizeof(struct ethhdr) );
  iphdrlen = iph->ihl*4;
    
  struct tcphdr *tcph=(struct tcphdr*)(Buffer + iphdrlen + sizeof(struct ethhdr));
            
  int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;
    
  fprintf(logfile , "\n\n***********************TCP Packet*************************\n");  
        
  NetworkMonitorPrintIPHeader(Buffer,Size);
        
  fprintf(logfile , "\n");
  fprintf(logfile , "TCP Header\n");
  fprintf(logfile , "   |-Source Port          : %u\n",ntohs(tcph->source));
  fprintf(logfile , "   |-Destination Port     : %u\n",ntohs(tcph->dest));
  fprintf(logfile , "   |-Sequence Number      : %u\n",ntohl(tcph->seq));
  fprintf(logfile , "   |-Acknowledge Number   : %u\n",ntohl(tcph->ack_seq));
  fprintf(logfile , "   |-Header Length        : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
  //fprintf(logfile , "   |-CWR Flag : %d\n",(unsigned int)tcph->cwr);
  //fprintf(logfile , "   |-ECN Flag : %d\n",(unsigned int)tcph->ece);
  fprintf(logfile , "   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
  fprintf(logfile , "   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
  fprintf(logfile , "   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
  fprintf(logfile , "   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
  fprintf(logfile , "   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
  fprintf(logfile , "   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
  fprintf(logfile , "   |-Window               : %d\n",ntohs(tcph->window));
  fprintf(logfile , "   |-Checksum             : %d\n",ntohs(tcph->check));
  fprintf(logfile , "   |-Urgent Pointer       : %d\n",tcph->urg_ptr);
  fprintf(logfile , "\n");
  fprintf(logfile , "                        DATA Dump                         ");
  fprintf(logfile , "\n");
        
  Buffer += sizeof(struct ethhdr);
  fprintf(logfile , "IP Header\n");
  NetworkMonitorPrintData(Buffer,iphdrlen);
        
  fprintf(logfile , "TCP Header\n");
  NetworkMonitorPrintData(Buffer+iphdrlen,tcph->doff*4);
        
  fprintf(logfile , "Data Payload\n");    
  NetworkMonitorPrintData(Buffer + header_size , Size - header_size );
                        
  fprintf(logfile , "\n###########################################################");
}

