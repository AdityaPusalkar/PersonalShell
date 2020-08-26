#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 

void shell_input()
{

}
void shell_loop()
{
    char *input;
    int nums = 10;
    do
    {
        printf("--> ");
        input = shell_input();
        free(input);
        n--;
    } while(n);
}

int main(int argc, char **argv)
{
    printf("Welcome to my Shell!");
    shell_input();
    return EXIT_SUCCESS;
}
