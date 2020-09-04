#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>

void shell_cd(int param, char** args)
{
    if(param==1)
    {
        printf("Please Enter Directory Name");
    }
    else
    {
        if(chdir(args[1]) == 0)
        {
            char s[100];
            printf("Directory changed to: %s",getcwd(s, 100));
        }
        else
        {
            printf("Invalid Directory Name");
        }
        
    }
}