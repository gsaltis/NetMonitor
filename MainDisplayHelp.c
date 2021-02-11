/*****************************************************************************!
 * Function : MainDisplayHelp
 *****************************************************************************/
void
MainDisplayHelp
()
{
  printf("Usage %s options\n", mainProgramName);
  printf("OPTIONS\n");
  printf("  -h, --help                                             : Display this information\n");
  printf("  -a, --address <interface> <ipaddress> {gatewayaddress} : Set the interfaces IP4 address and optionally the gateway address\n");
  printf("  -d, --display                                          : Display the interface information\n");
  printf("  -l, --logfile                                          : Specify the log filename. %s(default %s)%s\n", ColorRed, logFilenameDefault, ColorReset);
  printf("  -L, --log                                              : Specify whether to log packets %s(default %s)%s\n", ColorRed, NetworkMonitorGetLogging() ? "true" : "false", ColorReset);
  printf("  -i, --interface <name>                                 : Specify the interface to be monitored %s(default %s)%s\n", ColorRed, networkMonitorInterfaceNameDefault, ColorReset);
  printf(" -in, --interfaces                                       : Display available interfaces\n");
  printf(" -ln, --logfilename <name>                               : Specify the monitor packet log file name %s(default %s)%s\n", ColorRed, NetworkMonitorGetLogName(), ColorReset);
}

