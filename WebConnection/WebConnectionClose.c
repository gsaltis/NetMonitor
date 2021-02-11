/*****************************************************************************!
 * Function : WebConnectionClose
 *****************************************************************************/
void
WebConnectionClose
(WebConnection* InConnection)
{
  if ( NULL == InConnection ) {
    return;
  }
  mg_send_websocket_frame(InConnection->connection, WEBSOCKET_OP_CLOSE,
                          NULL, 0);
}
