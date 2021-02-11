/*****************************************************************************!
 * Function : UserInterfaceProcessCommand
 *****************************************************************************/
void
UserInterfaceProcessCommand
(StringList* InCommand)
{
  string                                command;
  if ( NULL == InCommand ) {
    return;
  }
  if ( InCommand->stringCount == 0 ) {
    return;
  }

  command = InCommand->strings[0];
  if ( StringEqualNoCase(command, "quit") ) {
    UserInterfaceProcessCommandQuit(InCommand);
    return;
  }

  if ( StringEqualNoCase(command, "help") ) {
    UserInterfaceProcessCommandHelp(InCommand);
    return;
  }
}


