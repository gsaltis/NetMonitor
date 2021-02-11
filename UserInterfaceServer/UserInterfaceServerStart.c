/*****************************************************************************!
 * Function : UserInterfaceServerStart
 *****************************************************************************/
void
UserInterfaceServerStart
()
{
  if ( pthread_create(&UserInterfaceServerID, NULL, UserInterfaceServerThread, NULL) ) {
    fprintf(stderr, "Could not start User Input Server : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
}


