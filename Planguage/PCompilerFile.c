void openFile(char *fs)
{
  //open the file
  input = fopen(fs,"r");
  //set the line cursor to 0
  lineCursor=0;
}
void skipHead()
{
  //set the cursor to the first useful data
  inputBufferCursor=0;
  while(inputBuffer[inputBufferCursor]==' '||inputBuffer[inputBufferCursor]=='\t') inputBufferCursor++;
}
void skipComments()
{
  // the "//"
  if(inputBuffer[inputBufferCursor]==inputBuffer[inputBufferCursor+1]=='/')
  {
    //
  }
  else if(inputBuffer[inputBufferCursor]=='/' && inputBuffer[inputBufferCursor]=='*')
  {
    //
    status = STATUS_COMMENTS;
  }
}
void readLine()
{
  //put the line into the buffer
  for(;;)
  {//inifite loop enabled
    fgets(inputBuffer,BUFFER_LENGTH,input);
    lineCursor++;
    skipHead();
    //met the "//" problem, read next line
    //met the /* problem, find
  }
}
