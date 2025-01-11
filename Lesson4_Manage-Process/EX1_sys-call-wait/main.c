#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char* argv[])
{
    int return_value;
    int status;
    pid_t child_pid;

    child_pid = fork();
    if(child_pid == 0)
    {
        /*child process*/
        printf("I'm the child process, my PID is %d\n", getpid());
        printf("The child process terminate after 4 seconds\n");
        sleep(4);
        // while(1);
        exit(0);
    }else
    {
        /*parent process*/
        // while(1);
        return_value = wait(&status);
        if(return_value == -1)
        {
            printf("wait() unsuccessful!");
        }
        
        printf("\nI'm the parent process, PID child process is %d and status is %d\n", return_value, status);

        if(WIFEXITED(status))
        {
            printf("\nNormally termination, status = %d\n", WEXITSTATUS(status));
        }else if(WIFSIGNALED(status))
        {
            printf("Abnormally termination, signal value = %d\n", WTERMSIG(status));
        }
    }

    return 0;
}