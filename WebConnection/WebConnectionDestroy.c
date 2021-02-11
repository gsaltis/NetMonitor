/*****************************************************************************!
 * Function : WebConnectionDestroy
 *****************************************************************************/
void
WebConnectionDestroy
(WebConnection* InConnection)
{
  if ( NULL == InConnection ) {
    return;
  }
  FreeMemory(InConnection);
}
