void shell_chmod(int param, char** args)
{
    if(param!=3)
    {
        printf("Invalid number of Arguments");
    }
    else
    {
        int A = 0|atoi(args[1]);
        printf("%d\n", A);
        int octA = 0,num = 1;
        while(A>0)
        {
            octA += (A%10)*num;
            num = num*8;
            A = A/10;
        }
        printf("%d\n", octA);
        if(chmod(args[2],octA)!=0)
        {
            perror("chmod");
        }
        else
        {
            printf("File mode successfully changes");
        }
    }
}
