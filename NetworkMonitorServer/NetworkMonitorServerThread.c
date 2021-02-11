/*****************************************************************************!
 * Function : NetworkMonitorServerThread
 *****************************************************************************/
void*
NetworkMonitorServerThread
(void* InParameters)
{
  UserInterfaceServerStart();
  NetworkMonitorInterface();
  return NULL;
}

