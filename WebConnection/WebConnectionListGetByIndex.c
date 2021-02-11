/*****************************************************************************!
 * Function : WebConnectionListGetByIndex
 *****************************************************************************/
WebConnection*
WebConnectionListGetByIndex
(WebConnectionList* InList, int InIndex)
{
  int                                   count;
  WebConnection*                        connection;

  pthread_mutex_lock(&InList->lock);
  if ( InList == NULL || InIndex < 0 ) {
    pthread_mutex_unlock(&InList->lock);
    return NULL;
  }

  count = 0;

  for ( connection = InList->first; connection; connection = connection->next ) {
    if ( count == InIndex ) {
      pthread_mutex_unlock(&InList->lock);
      return connection;
    }
    count++;
  }
  pthread_mutex_unlock(&InList->lock);
  return NULL;
}
