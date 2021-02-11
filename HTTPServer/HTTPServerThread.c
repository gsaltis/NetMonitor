/*****************************************************************************!
 * Function : HTTPServerThread
 *****************************************************************************/
void*
HTTPServerThread
(void* InParameters)
{
  mg_mgr_init(&HTTPManager, NULL);
  HTTPConnection = mg_bind(&HTTPManager, WebSocketHTTPGetHTTPPortAddress(), HTTPServerEventHandler);

  if ( NULL == HTTPConnection ) {
    fprintf(stderr, "%sFailed to create HTTP server%s\n", ColorBrightRed, ColorReset);
    exit(EXIT_FAILURE);
  }

  mg_set_protocol_http_websocket(HTTPConnection);
  HTTPServerOptions.document_root = WebSocketHTTPGetWWWDirectory();
  HTTPServerOptions.enable_directory_listing = "yes";
  WebSocketServerStart();
  while ( true ) {
    mg_mgr_poll(&HTTPManager, HTTPServerPollPeriod);
  }
}
