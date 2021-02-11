/*****************************************************************************!
 * Function : MainProcessCommandLine
 *****************************************************************************/
void
MainProcessCommandLine
(int argc, char** argv)
{
  StringList*                           s2;
  string                                s;
  int                                   n;
  int                                   i;
  string                                command;

  for (i = 1; i < argc; i++) {
    command = argv[i];
    if ( StringEqualsOneOf(command, "-h", "--help", NULL) ) {
      MainDisplayHelp();
      exit(EXIT_SUCCESS);
    }
    if ( StringEqualsOneOf(command, "-d", "--display", NULL) ) {
      mainDisplayInterfaces = true;
      continue;
    }
    if ( StringEqualsOneOf(command, "-l", "--logfile", NULL) ) {
      i++;
      if ( i == argc ) {
        fprintf(stderr, "\"%s\" must include a filename\n", command);
        MainDisplayHelp();
        exit(EXIT_FAILURE);
      }
      LogSetFilename(argv[i]);
      continue;
    }
    if ( StringEqualsOneOf(command, "-m", "--monitor", NULL) ) {
      mainMonitorInterface = true;
      n = i +1;
      if ( argc == n ) {
        continue;
      }
      if ( StringBeginsWith(argv[n], "-") ) {
        continue;
      }
      if ( mainFilterAddress ) {
        FreeMemory(mainFilterAddress);
      }
      mainFilterAddress = StringCopy(argv[n]);
      i++;
      continue;
    }
    if ( StringEqualsOneOf(command, "-a", "--address", NULL) ) {
      if ( i + 2 >= argc ) {
        fprintf(stderr, "%s\"%s\" requires an interface name and an IP address%s\n",
                ColorBrightRed, command, ColorReset);
        MainDisplayHelp();
        exit(EXIT_FAILURE);
      }
      i++;
      mainInterfaceName = StringCopy(argv[i]);
      i++;
      mainNewIPAddress = StringCopy(argv[i]);
      n = i + 1;
      if ( n + 1 < argc ) {
        s = argv[n];
        if ( StringBeginsWith(s, "-") ) {
          continue;
        }
        i++;
        mainNewGatewayAddress = StringCopy(argv[i]);
      } else {
        s2 = StringSplit(mainNewIPAddress, ".", false);
        if ( NULL == s2 || s2->stringCount != 4 ) {
          fprintf(stderr, "%s\"%s\" does not appear to be valid IP4 address%s\n",
                  ColorBrightRed, mainNewIPAddress, ColorReset);
          MainDisplayHelp();
          exit(EXIT_FAILURE);
        } else {
          mainNewGatewayAddress = StringMultiConcat(s2->strings[0], ".",
                                                    s2->strings[1], ".",
                                                    s2->strings[2], ".",
                                                    "1",
                                                    NULL);
        }
        StringListDestroy(s2);
      }
      mainSetIPAddress = true;
      continue;
    }
    fprintf(stderr, "%s\"%s\" is not a valid command%s\n", ColorBrightRed, command, ColorReset);
    MainDisplayHelp();
    exit(EXIT_FAILURE);
  }
}


