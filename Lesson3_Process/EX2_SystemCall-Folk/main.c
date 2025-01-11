#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int a = 0;
    __pid_t child_pid;

    printf("Gia tri khoi tao cua a: %d\n", a);

    child_pid = fork();

    if(child_pid == 0)
    {
        /*child process*/
        printf("\nI'm the child process, a: %d \n",--a);
        printf("My PID is: %d, My parent PID is: %d\n", getpid(), getppid());
    }else
    {
        /*parent process*/
        printf("\nI'm the parent process, a: %d \n", a);
        printf("My PID is: %d\n", getpid());
    }

    return 0;
}