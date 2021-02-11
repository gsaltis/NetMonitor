/*****************************************************************************!
 * Function : MainInitialize
 *****************************************************************************/
void
MainInitialize
()
{
  LogInitialize();
  WebSocketHTTPInitialize();
  WebSocketServerInitialize();
  HTTPServerInitialize();
  UserInterfaceServerInitialize();
  NetworkMonitorInitialize();
}

