/*****************************************************************************!
 * Function : NetworkMonitorPrintIPHeader
 *****************************************************************************/
void
NetworkMonitorPrintIPHeader
(unsigned char* Buffer, int Size)
{
  struct sockaddr_in                    source,dest;
  
  NetworkMonitorPrintEthernetHeader(Buffer , Size);
        
  struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
    
  memset(&source, 0, sizeof(source));
  source.sin_addr.s_addr = iph->saddr;
    
  memset(&dest, 0, sizeof(dest));
  dest.sin_addr.s_addr = iph->daddr;
    
  fprintf(logfile , "\n");
  fprintf(logfile , "IP Header\n");
  fprintf(logfile , "   |-IP Version           : %d\n",(unsigned int)iph->version);
  fprintf(logfile , "   |-IP Header Length     : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
  fprintf(logfile , "   |-Type Of Service      : %d\n",(unsigned int)iph->tos);
  fprintf(logfile , "   |-IP Total Length      : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
  fprintf(logfile , "   |-Identification       : %d\n",ntohs(iph->id));
  //fprintf(logfile , "   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
  //fprintf(logfile , "   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
  //fprintf(logfile , "   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
  fprintf(logfile , "   |-TTL                  : %d\n",(unsigned int)iph->ttl);
  fprintf(logfile , "   |-Protocol             : %d\n",(unsigned int)iph->protocol);
  fprintf(logfile , "   |-Checksum             : %d\n",ntohs(iph->check));
  fprintf(logfile , "   |-Source IP            : %s\n",inet_ntoa(source.sin_addr));
  fprintf(logfile , "   |-Destination IP       : %s\n",inet_ntoa(dest.sin_addr));
}


