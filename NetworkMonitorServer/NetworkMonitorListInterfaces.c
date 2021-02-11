/*****************************************************************************!
 * Function : NetworkMonitorListInterfaces
 *****************************************************************************/
void
NetworkMonitorListInterfaces
()
{
  int                                   address;
  int                                   n;
  StringList*                           interfaces;
  int                                   i;
  int                                   maxLen;
  char                                  s[33];
  
  maxLen = 0;
  interfaces = NetworkMonitorGetNetworkInterfaces();
  for (i = 0; i < interfaces->stringCount; i++ ) {
    n = strlen(interfaces->strings[i]);
    if ( n > maxLen ) {
      maxLen = n;
    }
  }
  for (i = 0; i < interfaces->stringCount ; i++ ) {
    address = NetworkMonitorGetInterfaceAddress(interfaces->strings[i]);
    printf("%2d : %*s : %s\n", i + 1, maxLen, interfaces->strings[i],
           inet_ntop(AF_INET, &address, s, 32));
  }
  StringListDestroy(interfaces);
}
