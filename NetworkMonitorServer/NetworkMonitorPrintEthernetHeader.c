/*****************************************************************************!
 * Function : NetworkMonitorPrintEthernetHeader
 *****************************************************************************/
void
NetworkMonitorPrintEthernetHeader
(unsigned char* Buffer, int Size)
{
  struct ethhdr *eth = (struct ethhdr *)Buffer;
    
  fprintf(logfile , "\n");
  fprintf(logfile , "Ethernet Header\n");
  fprintf(logfile , "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
  fprintf(logfile , "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
  fprintf(logfile , "   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
}


