/*****************************************************************************!
 * Function : WebConnectionListFind
 *****************************************************************************/
WebConnection*
WebConnectionListFind
(WebConnectionList* InList, struct mg_connection* InConnection)
{
  WebConnection*                        connection;

  pthread_mutex_lock(&InList->lock);
  if ( NULL == InList || NULL == InConnection ) {
    pthread_mutex_unlock(&InList->lock);
    return NULL;
  }
  for ( connection = InList->first; connection; connection = connection->next ) {
    if ( connection->connection == InConnection ) {
      pthread_mutex_unlock(&InList->lock);
      return connection;
    }
  }
  pthread_mutex_unlock(&InList->lock);
  return NULL;
}

