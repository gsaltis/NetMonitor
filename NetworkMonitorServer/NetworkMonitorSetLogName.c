/*****************************************************************************!
 * Function : NetworkMonitorSetLogName
 *****************************************************************************/
void
NetworkMonitorSetLogName
(string InLogName)
{
  if ( NULL == InLogName ) {
    return;
  }
  FreeMemory(networkLogFilename);
  networkLogFilename = StringCopy(InLogName);
}
