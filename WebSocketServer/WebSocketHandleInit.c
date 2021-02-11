/*****************************************************************************!
 * Function : WebSocketHandleInit
 *****************************************************************************/
void
WebSocketHandleInit
(struct mg_connection* InConnection, json_value* InJSONDoc)
{
  JSONOut*                              body;
  body = JSONOutCreateObject("body");
  JSONOutObjectAddObjects(body,
                          JSONOutCreateString("appname", mainAppName),
                          JSONOutCreateString("appdesc", mainAppDescription),
                          NULL);
  WebSocketServerSendResponse(InConnection, body, InJSONDoc, "init");
}

