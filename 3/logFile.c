#include <stdio.h>

void log(char* text)
{
  FILE *logFile = fopen("log.txt", "a");
  
  fprintf(logFile, "%s\n", text);
  
  fclose(logFile);
}