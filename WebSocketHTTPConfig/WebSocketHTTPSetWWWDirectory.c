/*****************************************************************************!
 * Function : WebSocketHTTPSetWWWDirectory
 *****************************************************************************/
void
WebSocketHTTPSetWWWDirectory
(string InWWWDirectory)
{
  if ( NULL == InWWWDirectory ) {
    return;
  }
  if ( WWWDirectory ) {
    FreeMemory(WWWDirectory);
  }
  WWWDirectory = StringCopy(WWWDirectoryDefault);
}

