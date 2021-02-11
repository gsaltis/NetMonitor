/*****************************************************************************!
 * Function : LogSetFilename
 *****************************************************************************/
void
LogSetFilename
(string InLogFilename)
{
  if ( InLogFilename ) {
    return;
  }
  if ( logFilename ) {
    FreeMemory(logFilename);
  }
  logFilename = StringCopy(InLogFilename);
}
