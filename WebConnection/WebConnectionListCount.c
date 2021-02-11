/*****************************************************************************!
 * Function : WebConnectionListCount
 *****************************************************************************/
int
WebConnectionListCount
(WebConnectionList* InList)
{
  WebConnection*                        connection;
  int                                   count;
 
  pthread_mutex_lock(&InList->lock);
  if ( InList == NULL ) {
    pthread_mutex_unlock(&InList->lock);
    return 0;
  }
 
  count = 0; 
  for ( connection = InList->first; connection; connection = connection->next ) {
    count++;
  }
  pthread_mutex_unlock(&InList->lock);
  return count;
}

