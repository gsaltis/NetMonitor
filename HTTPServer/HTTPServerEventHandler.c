/*****************************************************************************!
 * Function : HTTPServerEventHandler
 *****************************************************************************/
void
HTTPServerEventHandler
(struct mg_connection* InConnection, int InEvent, void* InParameter)
{
  if ( InEvent == MG_EV_HTTP_REQUEST ) {
    mg_serve_http(InConnection, (struct http_message*)InParameter, HTTPServerOptions);
  }
}
