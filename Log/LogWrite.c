/*****************************************************************************!
 * Function : LogWrite
 *****************************************************************************/
void
LogWrite
(string InFormat, ...)
{
  FILE*                                 file;
  va_list                               vlist;
  time_t                                t;
  struct tm*                            t2;

  t = time(NULL);
  if ( logFilename == NULL ) {
    return;
  }

  t2 = localtime(&t);
  file = fopen(logFilename, "ab");
  if ( NULL == file ) {
    return;
  }

  fprintf(file, "%04d/%02d/%04d %02d:%02d:%02d - ",
          t2->tm_year + 1900, t2->tm_mon + 1, t2->tm_mday,
          t2->tm_hour, t2->tm_min, t2->tm_sec); 
  va_start(vlist, InFormat);
  vfprintf(file, InFormat, vlist);
  fclose(file);
}

