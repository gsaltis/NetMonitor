/*****************************************************************************!
 * Function : UserInterfaceParseCommandLine
 *****************************************************************************/
StringList*
UserInterfaceParseCommandLine
(string InCommandLine)
{
  string                                s;
  int                                   n;
  string                                start;
  string                                end;
  StringList*                           commands;
  enum
  {
   InStart = 1,
   InSpaces,
   InToken,
   InSingleQuotedString,
   InDoubleQuotedString,
   InDone
  } state = InStart;
  
  if ( NULL == InCommandLine ) {
    return NULL;
  }
  if ( StringContainsChar(InCommandLine, '"') ) {
    commands = StringListCreate();
    start = InCommandLine;
    end = start;
    while ( state != InDone ) {
      if ( *end == 0x00 ) {
        switch (state) {
          case InStart : {
            break;
          }
          case InDone : {
            break;
          }
          case InSpaces : {
            break;
          }
          case InToken : {
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            break;
          }
          case InDoubleQuotedString : {
            start++;
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            break;
          }
          case InSingleQuotedString : {
            start++;
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            break;
          }
        }
        state = InDone;
        continue;
      }
      switch (state) {
        case InDone : {
          break;
        }
          
          //!
        case InStart : {
          if ( *start == 0x00 ) {
            state = InDone;
            break;
          }
          if (isspace(*start) ) {
            start++;
            state = InSpaces;
            break;
          }
          if ( *start == '"' ) {
            end = start;
            end++;
            state = InDoubleQuotedString;
            break;
          }
          if  ( *start == '\'' ) {
            end = start;
            end++;
            state = InSingleQuotedString;
            break;
          }
          end = start;
          end++;
          state = InToken;
          break;
        }
          //!
        case InSpaces : {
          if ( *start == 0x00 ) {
            state = InDone;
            break;
          }
          
          if ( isspace(*start) ) {
            start++;
            break;
          }
          if ( *start == '"' ) {
            end = start;
            end++;
            state = InDoubleQuotedString;
            break;
          }
          if  ( *start == '\'' ) {
            end = start;
            end++;
            state = InSingleQuotedString;
            break;
          }
          end = start;
          end++;
          state = InToken;
          break;
        }

          //!
        case InToken : {
          if ( *end == 0x00 ) {
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            state = InDone;
            break;
          }
          
          if ( isspace(*end) ) {
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            start = end;
            state = InSpaces;
            break;
          }
          end++;
          break;
        }

          //!
        case InSingleQuotedString : {
          if (*end == '\\' ) {
            end++;
            if ( *end ) {
              end++;
              break;
            }
            state = InDone;
            break;
          }
          if ( *end == 0x00 ) {
            start++;
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            state = InDone;
            break;
          }
          if ( *end == '\'' ) {
            start++;
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            end++;
            start = end;
            if ( *end == 0x00 ) {
              state = InDone;
              break;
            }
            if ( isspace(*start) ) {
              state = InSpaces;
              end++;
              break;
            }
            if ( *start == '"' ) {
              state = InDoubleQuotedString;
              end++;
              break;
            }
            if ( *start == '\'' ) {
              state = InSingleQuotedString;
              end++;
              break;
            }
            end++;
            state = InToken;
            break;
          }
          end++;
          break;
        }
          
          //!
        case InDoubleQuotedString : {
          if (*end == '\\' ) {
            end++;
            if ( *end ) {
              end++;
              break;
            }
            state = InDone;
            break;
          }
          if ( *end == 0x00 ) {
            start++;
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            state = InDone;
            break;
          }            
          if ( *end == '"' ) {
            start++;
            n = end - start;
            s = StringNCopy(start, n);
            StringListAppend(commands, s);
            end++;
            start = end;
            if ( *end == 0x00 ) {
              state = InDone;
              break;
            }
            if ( isspace(*start) ) {
              state = InSpaces;
              end++;
              break;
            }
            if ( *start == '"' ) {
              state = InDoubleQuotedString;
              end++;
              break;
            }
            if ( *start == '\'' ) {
              state = InSingleQuotedString;
              end++;
              break;
            }
            end++;
            state = InToken;
            break;
          }
          end++;
          break;
        }
      }
    }
  } else {
    commands = StringSplit(InCommandLine, " \t", true);
  }
  return commands;
}


