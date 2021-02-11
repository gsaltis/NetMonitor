/*****************************************************************************!
 * Function : WebConnectionListCreate
 *****************************************************************************/
WebConnectionList*
WebConnectionListCreate
()
{
  WebConnectionList*                    list;

  list = (WebConnectionList*)GetMemory(sizeof(WebConnectionList));
  pthread_mutex_init(&list->lock, NULL);
  list->first = NULL;
  list->last  = NULL; 
  return list;
}

