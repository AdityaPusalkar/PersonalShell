#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>
// custom files
#include"ls.h"
#include"cd.h"
#include"cat.h"
#include"mkdir.h"
#include"mv.h"
#include"grep.h"
#include"chmod.h"
#include"rm.h"
#include"cp.h"

// function to execute processes in the backfground
void shell_bg(int index, char** args)
{
  int forkid = fork();
  if(forkid<0)
  {
    perror("Error while forking");
  }
  else if(forkid==0)
  {
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
    else if(strcmp(args[0], "cp")==0)
    {
      shell_cp(index,args);
    }
    else // execute inbuilt commands in the background
    {
      args[index]=NULL;
      if(execvp(args[0],args)<0)
        perror(args[0]);
    }
  }
  else
  {
    return;
  }
}

// separate inputs into the respective arguments
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
  // tokenize input
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

// take input from standard input
char *shell_input()
{
  char *input = NULL;
  size_t bufsize = 0;
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

// take input from the user until exited otherwise
void shell_loop()
{
    char *input;
    char **args;
    while(1)
    {
      // formatting the shell
      printf("\033[1;34m");
      char s[100];
      printf("%s\n",getcwd(s, 100));
      printf("--> $ ");
      input = shell_input();
      printf("\033[1;32m");
      printf("You entered: %s",input);
      args = shell_parse(input);
      int index = 0;
      while(args[index]!=NULL)
      {
        index++;
      }
      // Exit the shell
      if(strcmp(args[0],"exit")==0)
      {
        exit(0);
      }
      // Background Execution
      else if(strcmp(args[index-1],"&")==0)
      {
        shell_bg(index-1,args);
      }
      // Implemented Functions
      else if(strcmp(args[0],"ls")==0)
      {
        shell_ls(index,args);
      }
      else if(strcmp(args[0],"cd")==0)
      {
        shell_cd(index,args);
      }
      else if(strcmp(args[0], "pwd")==0)
      {
        // direct execution
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
      else if(strcmp(args[0], "cp")==0)
      {
        shell_cp(index,args);
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
    printf("Features:\n");
    printf("1: Executing Inbuilt Commands\n");
    printf("2: Implemented ls, cd, pwd, cat, mkdir, mv, grep, chmod, rm, cp\n");
    printf("3: Background execution using &\n");
    shell_loop(); // take input and loop
    return EXIT_SUCCESS;
}
