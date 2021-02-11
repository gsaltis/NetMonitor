/*****************************************************************************!
 * Function : NetworkMonitorSetInterfaceName
 *****************************************************************************/
void
NetworkMonitorSetInterfaceName
(string InInterfaceName)
{
  if ( NULL == InInterfaceName ) {
    return;
  }

  FreeMemory(networkMonitorInterfaceName);
  networkMonitorInterfaceName = StringCopy(InInterfaceName);
}
