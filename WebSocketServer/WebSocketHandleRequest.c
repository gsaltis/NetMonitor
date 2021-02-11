/*****************************************************************************!
 * Function : WebSocketHandleRequest
 *****************************************************************************/
void
WebSocketHandleRequest
(struct mg_connection* InConnection, json_value* InJSONDoc)
{
  string                                type;

  type = JSONIFGetString(InJSONDoc, "type");
  WebSocketPacketID = JSONIFGetInt(InJSONDoc, "packetid");
  if ( StringEqual(type, "init") ) {
    WebSocketHandleInit(InConnection, InJSONDoc);
  }
  FreeMemory(type);
}
