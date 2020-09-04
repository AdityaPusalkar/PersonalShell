#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>
#include"ls.h"
#include"cd.h"
#include"cat.h"
#include"mkdir.h"
#include"mv.h"
#include"grep.h"
#include"chmod.h"
#include"rm.h"

char **shell_parse(char *input)
{
  int buflen = 48;
  int len = buflen;
  int index = 0;
  char **args = malloc(len * sizeof(char*));
  char *arg;
  if (!args) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  char *delim = " \t\r\n\a";
  arg = strtok(input,delim);
  while(arg!=NULL)
  {
    args[index] = arg;
    index++;
    if(index>=len)
    {
      len+=buflen;
      args = realloc(args, len * sizeof(char*));
      if(!args)
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    arg = strtok(NULL, delim);
  } 
  args[index] = NULL;
  return args;
}

char *shell_input()
{
  char *input = NULL;
  ssize_t bufsize = 0;
  if (getline(&input, &bufsize, stdin) == -1)
  {
    if (feof(stdin)) 
    {
      exit(EXIT_SUCCESS);
    } 
    else  
    {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }
  return input;
}
void shell_loop()
{
    char *input;
    char **args;
    while(1)
    {
      printf("\033[1;34m");
      printf("--> ");
      input = shell_input();
      printf("\033[1;32m");
      printf("You entered: %s",input);
      args = shell_parse(input);
      int index = 0;
      while(args[index]!=NULL)
      {
        index++;
      }
      // Implemented Functions
      if(strcmp(args[0],"ls")==0)
      {
        shell_ls(index,args);
      }
      else if(strcmp(args[0],"cd")==0)
      {
        shell_cd(index,args);
      }
      else if(strcmp(args[0], "pwd")==0)
      {
        char s[100];
        printf("%s",getcwd(s, 100));
      }
      else if(strcmp(args[0], "cat")==0)
      {
        shell_cat(index,args);
      }
      else if(strcmp(args[0], "mkdir")==0)
      {
        shell_mkdir(index,args);
      }
      else if(strcmp(args[0], "mv")==0)
      {
        shell_mv(index,args);
      }
      else if(strcmp(args[0], "grep")==0)
      {
        shell_grep(index,args);
      }
      else if(strcmp(args[0], "chmod")==0)
      {
        shell_chmod(index,args);
      }
      else if(strcmp(args[0], "rm")==0)
      {
        shell_rm(index,args);
      }
      //To execute commands which are inbuilt
      else
      {
        int forkid = fork();
        if(forkid<0)
        {
          perror("Error while forking");
          exit(EXIT_FAILURE);
        }
        else if(forkid==0)
        {
          if(execvp(args[0], args) < 0)
          {
            perror(args[0]);
            exit(EXIT_FAILURE);
          }
        }
        else
        {
          int stat;
          waitpid(forkid, &stat, 0);
          continue;
        }
      }
      printf("\n");
      free(input);
      free(args);
    }
}

int main(int argc, char **argv)
{
    printf("\033[1;32m");
    printf("Welcome to Aditya's Shell!\n");
    printf("Features so Far:\n");
    printf("1: Accepting Input\n");
    printf("2: Executing Inbuilt Commands\n");
    printf("3: Implemented ls, cd, pwd, cat, mkdir, mv, grep, chmod, rm\n");
    shell_loop();
    return EXIT_SUCCESS;
}
