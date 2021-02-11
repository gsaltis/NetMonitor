/*****************************************************************************!
 * Function : WebSocketServerInitialize
 *****************************************************************************/
void
WebSocketServerInitialize
()
{
  WebSocketConnections = WebConnectionListCreate();
  WebSocketServerID = 0;
}
