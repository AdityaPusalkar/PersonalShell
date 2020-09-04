void shell_grep(int param, char** args)
{
    if(param!=3)
    {
        printf("Wrong format: use grep [pattern] [filename]");
    }
    else
    {
        struct stat filestat;
        if(stat(args[2],&filestat)!= -1)
        {
            FILE *file;
            if((file = fopen(args[2], "r")) == NULL) 
            {
                fprintf(stdout, "%s: %s : %s", args[0], args[2], strerror(errno));
                return;
            }
            if(!S_ISREG(filestat.st_mode))
            {
                fprintf(stdout,"Parameter is not a file");
            }
            else
            {
                int chr,ind;
                char line[100];
                while((chr = getc(file)) != EOF)
                {
                    if(chr!='\n')
                    {
                        line[ind]=chr;
                        ind++;
                    }
                    else
                    {
                        if(strstr(line,args[1])!=NULL)
                        {
                            int space = 0;
                            while(line[space]==' ')
                                space+=1;
                            for(int i=space; i<ind; i++)
                            {
                                printf("%c",line[i]);
                            }
                            printf("\n");
                        }   
                        memset(line,0,sizeof(line));
                        ind=0;
                    }
                }
            }            
        }
        else
        {
            printf("File: %s does not exist",args[2]);
        }  
    }
}