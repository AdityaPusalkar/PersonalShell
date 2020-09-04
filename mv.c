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