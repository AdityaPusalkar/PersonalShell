#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>

void shell_mv(int param, char** args)
{
    if(param!=3)
    {
        printf("Invalid number of operands, enter source and destination files/directories only");
    }
    else
    {
        if(rename(args[1],args[2])==0)
        {
            printf("File rename/move successful");
        }
        else
        {
            perror("rename");
        }               
    }  
}
