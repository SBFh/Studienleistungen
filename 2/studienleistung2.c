#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
  ProcessPlot("x");
  ProcessPlot("x*x");
  ProcessPlot("sin(x)");
  ProcessPlot("5*x*tan(x)");
  getchar();
}

int ProcessPlot(char* function)
{
  char command[255];
  strcpy(command, "plot ");
  strcat(command, function);
  strcat(command, "\n");
	 
  printf("Plotting Chart Command %s\n", command);
  
  int fd1[2], fd2[2];
  
  pipe(fd1);
  pipe(fd2);
  
  if (fork() == 0)
  {
    close(fd1[1]);
    close(fd2[0]);
    
    dup2(fd1[0], STDIN_FILENO);
    close(fd1[0]);
    
    dup2(fd2[1], STDOUT_FILENO);
    close(fd2[1]);
    
    execlp ("gnuplot", "gnuplot", (char *)0, (char *)0);
    printf("Error");
    return 0;
  }
  
  close(fd1[0]);
  close(fd2[1]);
  
  write(fd1[1], command, strlen(command));
  
  return 1;
}