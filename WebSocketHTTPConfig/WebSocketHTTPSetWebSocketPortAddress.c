/*****************************************************************************!
 * Function : WebSocketHTTPSetWebSocketPortAddress
 *****************************************************************************/
void
WebSocketHTTPSetWebSocketPortAddress
(string InWebSocketPortAddress)
{
  if ( NULL == InWebSocketPortAddress ) {
    return;
  }
  if ( WebSocketPortAddress ) {
    FreeMemory(WebSocketPortAddress);
  }
  WebSocketPortAddress = StringCopy(WebSocketPortAddressDefault);
  
}
