/*****************************************************************************!
 * Function : NetworkMonitorInitialize
 *****************************************************************************/
void
NetworkMonitorInitialize
()
{
  mainSetIPAddress              = false;
  mainDisplayInterfaces         = false;
  networkMonitorServerID        = 0;
  networkMonitorInterfaceName   = StringCopy(networkMonitorInterfaceNameDefault);
  networkLogFilename            = StringCopy(networkLogFilenameDefault);
}

