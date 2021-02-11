/*****************************************************************************!
 * Function : WebSocketHTTPSetHTTPPortAddress
 *****************************************************************************/
void
WebSocketHTTPSetHTTPPortAddress
(string InHTTPPortAddress)
{
  if ( NULL == InHTTPPortAddress ) {
    return;
  }
  if ( HTTPPortAddress ) {
    FreeMemory(HTTPPortAddress);
  }
  HTTPPortAddress = StringCopy(HTTPPortAddressDefault);
}
