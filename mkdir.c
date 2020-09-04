#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>

void shell_mkdir(int param, char** args)
{
    if(param==1)
    {
        printf("Missing operand");
    }
    else if(param>2)
    {
        printf("Only 1 Operand expected");
    }
    else
    {
        struct stat filestat;
        if(stat(args[1],&filestat)== -1)
        {
            mkdir(args[1],0777);
            printf("File Created");
        }
        else
        {
            printf("File: %s already exists",args[1]);
        }  
    }
}