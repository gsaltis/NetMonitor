/*****************************************************************************!
 * Function : WebSocketServerSendResponse
 *****************************************************************************/
void
WebSocketServerSendResponse
(struct mg_connection * InConnection, JSONOut* InBody, json_value* InJSONDoc, string InResponseType)
{
  string                                s;
  JSONOut*                              object;

  object = JSONOutCreateObject(NULL);
  JSONOutObjectAddObjects(object,
                          JSONOutCreateString("packettype", "response"),
                          JSONOutCreateInt("packetid", JSONIFGetInt(InJSONDoc, "packetid")),
                          JSONOutCreateInt("time", (int)time(NULL)),
                          JSONOutCreateString("type", InResponseType),
                          JSONOutCreateString("status", "OK"),
                          InBody,
                          NULL);
  
  s = JSONOutToString(object, 0);
  WebSocketFrameSend(InConnection, s, strlen(s));
  FreeMemory(s);
  JSONOutDestroy(object);
}

