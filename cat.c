#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>

void shell_cat(int param, char** args) {
  FILE *file;
  if(param==1)
  {
    printf("Please enter filename");
  }
  else
  {
    for(int cnt = 1; cnt < param; cnt++) 
    {
      if((file = fopen(args[cnt], "r")) == NULL) 
      {
        fprintf(stdout, "%s: %s : %s", args[0], args[cnt], strerror(errno));
        continue;
      }
      struct stat filestat;
      stat(args[cnt], &filestat);
      if(!S_ISREG(filestat.st_mode))
      {
        fprintf(stdout,"Parameter is not a file");
      }
      else
      {
        int chr;
        while((chr = getc(file)) != EOF)
        {
          fprintf(stdout, "%c", chr);
        }
        fprintf(stdout,"\n");
      }
      fclose(file);
    }
  }
}