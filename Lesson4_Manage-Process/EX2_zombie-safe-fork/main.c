#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void signal_handler(int signum)
{
    printf("I'm in signal_handler()\n");
    wait(NULL);
}

int main(int argc, const char* argv[])
{
    pid_t child_pid = fork();

    if(child_pid == 0){
        printf("I am child, my PID: %d\n", getpid());
        while(1);
    }else{
        signal(SIGCHLD, signal_handler); //nhận tín hiệu trả về từ child-process, sau đó thực hiện signal_handler
        printf("I am parent\n");
        while(1);
    }
}