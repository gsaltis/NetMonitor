/*****************************************************************************!
 * Function : NetworkMonitorServerStart
 *****************************************************************************/
void
NetworkMonitorServerStart
()
{
  if ( pthread_create(&networkMonitorServerID, NULL, NetworkMonitorServerThread, NULL) ) {
    fprintf(stdout, "%sCould not start \"Network Monitor Server Thread\"%s\n", ColorRed, ColorReset);
    exit(EXIT_FAILURE);
  }
}

