#include <string,h>
#include <stdio.h>
#define BUFFER_LENGTH 4096
#define STATUS_CODE 0
#define STATUS_COMMENTS 1
/** Globel variables section **/
int lineCursor;
/**
 * status is used to mark if the content is in the comment section / normal section
 */
int status;
file *input;
char inputBuffer[BUFFER_LENGTH];
char parseBuffer[BUFFER_LENGTH];
int inputBufferCursor;
int parseBufferCursor;
/** function section **/
void openFile(char *fs);
void skipHead();
void skipComments();
void readLine();
