/*****************************************************************************!
 * Function : NetworkMonitorProcessPacket
 *****************************************************************************/
void NetworkMonitorProcessPacket(unsigned char* buffer, int size)
{
  string                                saddr;
  string                                daddr;
  struct sockaddr_in                    source,dest;

  //Get the IP Header part of this packet , excluding the ethernet header
  struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
  ++total;

  memset(&source, 0, sizeof(source));
  source.sin_addr.s_addr = iph->saddr;
    
  memset(&dest, 0, sizeof(dest));
  dest.sin_addr.s_addr = iph->daddr;

  saddr = StringCopy(inet_ntoa(source.sin_addr));
  daddr = StringCopy(inet_ntoa(dest.sin_addr));

  if ( mainFilterAddress ) {
    if ( !StringEqual(saddr, mainFilterAddress) && !StringEqual(daddr, mainFilterAddress) ) {
      FreeMemory(saddr);
      FreeMemory(daddr);
      return;
    }
  }
  switch (iph->protocol) //Check the Protocol and do accordingly...
  {
    case 1:  //ICMP Protocol
      ++icmp;
      NetworkMonitorPrintICMPPacket( buffer , size);
      break;
        
    case 2:  //IGMP Protocol
      ++igmp;
      break;
        
    case 6:  //TCP Protocol
      ++tcp;
      NetworkMonitorPrintTCPPacket(buffer , size);
      break;
        
    case 17: //UDP Protocol
      ++udp;
      NetworkMonitorPrintUDPPacket(buffer , size);
      break;
        
    default: //Some Other Protocol like ARP etc.
      ++others;
      break;
  }
  printf("TCP : %d   UDP : %d   ICMP : %d   IGMP : %d   Others : %d   Total : %d\r",
         tcp , udp , icmp , igmp , others , total);
  fflush(stdout);
  FreeMemory(saddr);
  FreeMemory(daddr);
}

