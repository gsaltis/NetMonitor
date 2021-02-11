/*****************************************************************************!
 * Function : WebConnectionListRemove
 *****************************************************************************/
void
WebConnectionListRemove
(WebConnectionList* InList, WebConnection* InConnection)
{
  WebConnection*                        n;
  WebConnection*                        p;

  pthread_mutex_lock(&InList->lock);
  if ( NULL == InList || NULL == InConnection ) {
    pthread_mutex_unlock(&InList->lock);
    return;
  }
  if ( InConnection == InList->first ) {
    if ( InList->first->next == NULL ) {
      InList->first = NULL;
      InList->last  = NULL;
    } else {
      InList->first = InList->first->next;
    }
  } else if ( InConnection == InList->last ) {
    if ( InList->last->prev == NULL ) {
      InList->first = NULL;
      InList->last  = NULL;
    } else {
      InList->last = InList->last->prev;
      InList->last->next = NULL;
    }
  } else {
    p = InConnection->prev;
    n = InConnection->next;
    n->prev = p;
    p->next = n;
  }
  pthread_mutex_unlock(&InList->lock);
}
