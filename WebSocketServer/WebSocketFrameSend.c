/*****************************************************************************!
 * Function : WebSocketFrameSend
 *****************************************************************************/
void
WebSocketFrameSend
(struct mg_connection* InConnection, string InBuffer, uint16_t InBufferLen)
{
  mg_send_websocket_frame(InConnection, WEBSOCKET_OP_TEXT,
                          InBuffer, InBufferLen);
}
