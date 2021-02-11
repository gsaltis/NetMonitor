/*****************************************************************************!
 * Function : NetworkMonitorPacketContainsAddress
 *****************************************************************************/
bool
NetworkMonitorPacketContainsAddress
(unsigned char* InBuffer, unsigned long InAddress)
{
  struct sockaddr_in                    source,dest;
  struct iphdr *iph = (struct iphdr *)(InBuffer  + sizeof(struct ethhdr) );
    
  memset(&source, 0, sizeof(source));
  source.sin_addr.s_addr = iph->saddr;
    
  memset(&dest, 0, sizeof(dest));
  dest.sin_addr.s_addr = iph->daddr;

  if ( source.sin_addr.s_addr == InAddress || dest.sin_addr.s_addr == InAddress ) {
    return true;
  }
  return false;
}
