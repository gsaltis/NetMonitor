/*****************************************************************************!
 * Function : HTTPServerStart
 *****************************************************************************/
void
HTTPServerStart
()
{
  if ( pthread_create(&HTTPServerThreadID, NULL, HTTPServerThread, NULL) ) {
    fprintf(stderr, "%s\"Could not start \"HTTP Server Thread\"%s\n", ColorRed, ColorReset);
    exit(EXIT_FAILURE);
  }
}
