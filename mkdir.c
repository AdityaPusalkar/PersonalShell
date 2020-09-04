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