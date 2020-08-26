#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

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
    int n = 10;
    do
    {
        printf("--> ");
        input = shell_input();
        printf("You entered: %s",input);
        args = shell_parse(input);
        int index = 0;
        printf("Space separated: \n");
        while(args[index]!=NULL)
        {
          printf("%d: %s\n",(index+1),args[index]);
          index++;
        }
        printf("\n");
        n--;
        free(input);
        free(args);
    } while(n>0);
}

int main(int argc, char **argv)
{
    printf("Welcome to my Shell!\n");
    shell_loop();
    return EXIT_SUCCESS;
}
