/*****************************************************************************!
 * Function : WebConnectionTimeUpdate
 *****************************************************************************/
void
WebConnectionTimeUpdate
(WebConnection* InConnection, time_t InCurrentTime)
{
  if ( InConnection == NULL || InCurrentTime == 0 ) {
    return;
  }
  InConnection->lastReceiveTime = InCurrentTime;
}

