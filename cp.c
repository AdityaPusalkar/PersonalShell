#include<stdio.h> 
#include<string.h> 
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<errno.h>

char *directory(char *path){
    char *token;
    char *dir;
    size_t len;
    token = strrchr(path, '/'); // finds last occurence of character '/'
    if(token==NULL) 
        return path; // return path itself if it is a file
    len = strlen(token);
    dir = malloc(len);
    memcpy(dir, token+1, len);
    return (char*)dir;
}

// function to copy a single file
void filecopy(char *fsrc, char *fdst){
    FILE *src, *dst;
    int ch;
    
    if((src = fopen(fsrc, "r")) && (dst=fopen(fdst, "w"))){
        while((ch=fgetc(src))!=EOF){
            fputc(ch, dst);
        }
        fclose(src);
        fclose(dst);
    }
    else{
        fprintf(stderr, "Filecopy: %s\n", strerror(errno));
        return;
    }
}

void shell_cp(int param, char** args)
{
    if(param==3)
    {
        filecopy(args[1], args[2]);
    }
    else if(param==4 && (strcmp(args[1], "-r")==0))
    {
        DIR *dir;
        // source directory
        if((dir=opendir(args[2]))==NULL){
            fprintf(stderr, "Directory inaccessible %s\n", strerror(errno));
            return;
        }
        char *dest = args[3];
        char *newfilename = directory(args[2]); // making path of destination
        strcat(dest, "/");
        strcat(dest, newfilename);
        
        // making folder with the same name in the destination directory
        if(mkdir(dest, 0777)==-1)
        {
            fprintf(stderr, "mkdir %s\n", strerror(errno));
            return;
        }

        struct dirent *d;
        while((d=readdir(dir))!=NULL)
        {
            char *source = strdup(args[2]);
            strcat(source, "/");
            strcat(source, d->d_name);

            // checking if current path is of a directory or a file, copy it if it's a file
            struct stat filestat;
            stat(source, &filestat);
            if(S_ISREG(filestat.st_mode))
            {
                char *newdest = strdup(dest);
                strcat(newdest, "/");
                strcat(newdest, directory(source));
                filecopy(source, newdest);
            }
        }
    }
    else if(strcmp(args[1], "-r")==0)
    {
        fprintf(stderr, "Invalid Format, try: cp -r <source_dir> <dest_dir>\n");
    }
    else
    {
        fprintf(stderr, "Invalid Format, try: cp <source_dir> <dest_dir>\n");
    }
}