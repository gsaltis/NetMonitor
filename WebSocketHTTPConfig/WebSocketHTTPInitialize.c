/*****************************************************************************!
 * Function : WebSocketHTTPInitialize
 *****************************************************************************/
void
WebSocketHTTPInitialize
()
{
  WWWDirectory = StringCopy(WWWDirectoryDefault);
  WebSocketPortAddress = StringCopy(WebSocketPortAddressDefault);
  HTTPPortAddress = StringCopy(HTTPPortAddressDefault);
}

