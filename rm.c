#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>

int recursive_remove(char *path) {
    DIR *dir = opendir(path);
    size_t pathlen = strlen(path);
    int r1 = -1;
    struct stat filestat;
    stat(path, &filestat);
    if(S_ISREG(filestat.st_mode))
    {
        remove(path);
        printf("File removed");
    }
    else
    {
        if (dir) {
            struct dirent *d;
            r1 = 0;
            
            while (!r1 && (d=readdir(dir))) {
                int r2 = -1;
                char *buf;
                size_t len;
                // Skip \"." and ".."
                if (!strcmp(d->d_name, ".") || !strcmp(d->d_name, ".."))
                    continue;
                len = pathlen + strlen(d->d_name) + 2; 
                buf = malloc(len);
                if (buf) {
                    struct stat fs;
                    snprintf(buf, len, "%s/%s", path, d->d_name);
                    if (!stat(buf, &fs)) {
                        if (S_ISDIR(fs.st_mode))
                            r2 = recursive_remove(buf);
                        else
                            r2 = unlink(buf);
                    }
                    free(buf);
                }
                r1 = r2;
            }
            closedir(dir);
        }
        else
        {
            printf("No directory named: %s",path);
            return 0;
        }
    }
    if (!r1)
        r1 = rmdir(path);
    return r1;
}

void shell_rm(int param, char** args)
{
    if(param==1)
        printf("Missing operands");
    else if((param == 2) && strcmp(args[1], "-r")==0)
        printf("Missing operands");
    else
    {
        if(param==2)
        {
            if(remove(args[1]))
                perror("rm");
            else
            {
                printf("File removed successfully");
            }
        }
        else if((param==3) && strcmp(args[1], "-r")==0)
        {
            recursive_remove(args[2]);
        }
        else
        {
            printf("Wrong format: rm [file] or rm -r [file/directory]");
        }
    } 
}