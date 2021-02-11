/*****************************************************************************!
 * Function : WebSocketServerEventHandler
 *****************************************************************************/
void
WebSocketServerEventHandler
(struct mg_connection* InConnection, int InEvent, void* InParameter)
{
  WebConnection*                        con;
  struct websocket_message*             message;
  
  if ( InEvent == 0 ) {
    return;
  }

  switch (InEvent) {
    case MG_EV_CLOSE : {
      con = WebConnectionListFind(WebSocketConnections, InConnection);
      if ( con ) {
        WebConnectionListRemove(WebSocketConnections, con);
      }
      break;
    }

    case MG_EV_WEBSOCKET_FRAME : {
      if ( NULL == WebConnectionListFind(WebSocketConnections, InConnection) ) {
        WebConnectionListAppend(WebSocketConnections, WebConnectionCreate(InConnection));
      }
      message = (struct websocket_message*)InParameter;
      WebSocketHandlePacket(InConnection, (string)message->data, message->size);
      break;
    }
  }
}

