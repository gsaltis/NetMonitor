/*****************************************************************************!
 * Function : WebSocketServerStart
 *****************************************************************************/
void
WebSocketServerStart
()
{
  WebSocketServerCreateInfoScript();
  if ( pthread_create(&WebSocketServerID, NULL, WebSocketServerThread, NULL) ) {
    fprintf(stdout, "%sCould not start \"Web Socket Server Thread\"%s\n", ColorRed, ColorReset);
    exit(EXIT_FAILURE);
  }
}


