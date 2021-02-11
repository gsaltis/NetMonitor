/*****************************************************************************!
 * Function : WebConnectionListAppend
 *****************************************************************************/
void
WebConnectionListAppend
(WebConnectionList* InList, WebConnection* InConnection)
{
  if ( NULL == InList || NULL == InConnection ) {
    return;
  }
  pthread_mutex_lock(&InList->lock);
  if ( InList->first ) {
    InList->last->next = InConnection;
    InConnection->prev = InList->last;
    InList->last = InConnection;
  } else {
    InList->first = InConnection;
    InList->last = InConnection;
  }
  pthread_mutex_unlock(&InList->lock);
}
