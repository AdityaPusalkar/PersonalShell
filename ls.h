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