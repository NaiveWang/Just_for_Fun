void openFile(char *s)
{
  //tokenlizer initializer
  //readfile
  input=fopen(s,"r");
  if(input==NULL)
  {
    errno=1;
  }
  else
  {
    //initialize the cursor and sole args
    tokenlizerStatus=TOKENLIZER_STATUS_CONTENT;
    instantListCursor=0;
    symbolTableCursor=0;
    lineBufferCursor=0;
    tokenBufferCursor=0;
    lineCursor=0;
    errno=0;
  }
}
char readLine()
{
  //read line into the line buffer
  //increase the line cursor
  if(fgets(lineBuffer,LENGTH_OF_LINE_BUFFER,input))
  {
    //success
    lineBufferCursor=0;
    lineCursor++;
    return -1;
  }
  else
  {
    return 0;
  }
}
symbol* addIdentifier();
instant* addInstant();
token* getToken();
void errorNotifier()
{
  //print error info via the error number
  printf("Error No.%d:",error);
  switch(errno)
  {
    case 1 : printf("cannot open file");break;
    default:printf("undefined errno");
  }
  printf(".\n");
}
