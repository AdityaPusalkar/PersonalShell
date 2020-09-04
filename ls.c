#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>

void shell_ls(int param, char** args)
{
    struct dirent **directories;
    int numdirs;
    if(param == 1)
    {
        numdirs = scandir(".", &directories, NULL, alphasort);
    }
    else
    {
        numdirs = scandir(args[1], &directories, NULL, alphasort);
    }
    if(numdirs<0)
    {
        perror("scandir");
    }
    else
    {
        for(int i=2;i<numdirs;i++)
        {
            printf("%s  ",directories[i]->d_name);
        }
    }
    free(directories);
}