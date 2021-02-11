/*****************************************************************************!
 * Function : UserInterfaceServerThread
 *****************************************************************************/
void*
UserInterfaceServerThread
(void* InParameter)
{
  StringList*                           command;
  string                                userInterfaceString;
  while (true) {
    userInterfaceString = linenoise(UserInterfaceCommandPrompt);
    command = UserInterfaceParseCommandLine(userInterfaceString);
    if ( NULL == command ) {
      continue;
    }
    if ( command->stringCount == 0 ) {
      free(userInterfaceString);
      StringListDestroy(command);
      continue;
    }
    UserInterfaceProcessCommand(command);
    StringListDestroy(command);
    linenoiseHistoryAdd(userInterfaceString);
    free(userInterfaceString);
  }
  return NULL;
}


