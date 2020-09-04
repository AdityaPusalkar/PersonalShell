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
        while(numdirs--)
        {
            printf("%s ",directories[numdirs]->d_name);
        }
    }
    free(directories);
}