/*****************************************************************************!
 * Function : LogInitialize
 *****************************************************************************/
void
LogInitialize
()
{
  logUsing = false;
  logFilename = StringCopy(logFilenameDefault);
}
