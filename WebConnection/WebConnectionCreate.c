/*****************************************************************************!
 * Function : WebConnectionCreate
 *****************************************************************************/
WebConnection*
WebConnectionCreate
(struct mg_connection* InConnection)
{
  WebConnection*                        connection;

  connection = (WebConnection*)GetMemory(sizeof(WebConnection));
  memset(connection, 0x00, sizeof(WebConnection));
  connection->lastReceiveTime = time(NULL);
  connection->next = NULL;
  connection->prev = NULL;
  connection->connection = InConnection;
  return connection;
}

