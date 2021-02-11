/*****************************************************************************!
 * Function : WebConnectionListDisplay
 *****************************************************************************/
void
WebConnectionListDisplay
(WebConnectionList* InList)
{
  int                                   i;
  WebConnection*                        connection;
  char                                  s2[24];
  uint32_t                              address;
  int                                   n;
  string                                s;
  char                                  timeString[65];
  time_t                                t;

  pthread_mutex_lock(&InList->lock);
  i = 1;
  connection = InList->first;
  t = time(NULL);
  while (connection) {
    address = connection->connection->sa.sin.sin_addr.s_addr;
    sprintf(s2, "%d.%d.%d.%d", (address & 0xFF), ((address >> 8) & 0xFF), ((address >> 16) & 0xFF), ((address >> 24) & 0xFF));
    n = printf("%2d : %s:%d ", i, s2, connection->connection->sa.sin.sin_port);
    n = 32 - n;
    s = StringFill(' ', n);
    printf("%s", s);
    FreeMemory(s);
    strftime(timeString, 64, "%m/%d/%G %H:%M:%S", localtime(&connection->lastReceiveTime));
    printf("%s %d\n", timeString, (int)(t - connection->lastReceiveTime));
    connection = connection->next;
    i++;
  }
  pthread_mutex_unlock(&InList->lock);
}
 
