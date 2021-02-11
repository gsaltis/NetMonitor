/*****************************************************************************!
 * Function : NetworkMonitorPrintData
 *****************************************************************************/
void
NetworkMonitorPrintData
(unsigned char* data , int Size)
{
  int i , j;
  for(i=0 ; i < Size ; i++)
  {
    if( i!=0 && i%16==0)   //if one line of hex printing is complete...
    {
      fprintf(logfile , "         ");
      for(j=i-16 ; j<i ; j++)
      {
        if(data[j]>=32 && data[j]<=128)
          fprintf(logfile , "%c",(unsigned char)data[j]); //if its a number or alphabet
                
        else fprintf(logfile , "."); //otherwise print a dot
      }
      fprintf(logfile , "\n");
    } 
        
    if(i%16==0) fprintf(logfile , "   ");
    fprintf(logfile , " %02X",(unsigned int)data[i]);
                
    if( i==Size-1)  //print the last spaces
    {
      for(j=0;j<15-i%16;j++) 
      {
        fprintf(logfile , "   "); //extra spaces
      }
            
      fprintf(logfile , "         ");
            
      for(j=i-i%16 ; j<=i ; j++)
      {
        if(data[j]>=32 && data[j]<=128) 
        {
          fprintf(logfile , "%c",(unsigned char)data[j]);
        }
        else 
        {
          fprintf(logfile , ".");
        }
      }
            
      fprintf(logfile ,  "\n" );
    }
  }
}

