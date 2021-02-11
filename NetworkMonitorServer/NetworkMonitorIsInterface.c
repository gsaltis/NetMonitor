/*****************************************************************************!
 * Function : NetworkMonitorIsInterface
 *****************************************************************************/
bool
NetworkMonitorIsInterface
(string InInterfaceName)
{
  StringList*                           interfaces;
  int                                   i;

  if ( NULL == InInterfaceName ) {
    return false;
  }

  interfaces = NetworkMonitorGetNetworkInterfaces();
  for ( i = 0; i < interfaces->stringCount ; i++ ) {
    if ( StringEqual(InInterfaceName, interfaces->strings[i]) ) {
      StringListDestroy(interfaces);
      return true;
    }
  }
  StringListDestroy(interfaces);
  return false;
}
