/*****************************************************************************!
 * Function : WebSocketServerThread
 *****************************************************************************/
void*
WebSocketServerThread
(void* InParameters)
{
  mg_mgr_init(&WebSocketManager, NULL);
  WebSocketConnection = mg_bind(&WebSocketManager, WebSocketHTTPGetWebSocketHTTPPortAddress(), WebSocketServerEventHandler);
  if ( NULL == WebSocketConnection ) {
    fprintf(stdout, "%sFailed to create WebSocket server%s\n", ColorBrightRed, ColorReset);
    exit(EXIT_FAILURE);
  }
  mg_set_protocol_http_websocket(WebSocketConnection);
  WebSocketServerOptions.document_root = WebSocketHTTPGetWWWDirectory();
  WebSocketServerOptions.enable_directory_listing = "yes";
  
  printf("%sWeb Socket Server Thread : %sstarted%s\n"
         "%s  Port                   : %s%s%s\n"
         "%s  Directory              : %s%s%s\n", 
         ColorGreen, ColorYellow, ColorReset,
         ColorCyan, ColorYellow, WebSocketHTTPGetHTTPPortAddress(), ColorReset, 
         ColorCyan, ColorYellow, WebSocketHTTPGetWWWDirectory(), ColorReset);
  WebSocketServerStartTime = time(NULL);
  NetworkMonitorServerStart();
  while ( true ) {
    mg_mgr_poll(&WebSocketManager, WebSocketServerPollPeriod);
  }
}

