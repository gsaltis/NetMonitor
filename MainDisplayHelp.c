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
  printf("  -l, --logfile                                          : Specify the log filename. (default %s)\n", logFilenameDefault);
  printf("  -m {ipaddress}                                         : Monitor a network interface\n");
}

