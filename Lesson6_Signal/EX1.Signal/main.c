#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int count = 0;

// Không nên sử dụng các hàm dạng sleep trong các signal
void sig_handler1(int num){
    printf("\nI am SIGINT: %d, counting: %d\n", num, count++);
    // while(1);
    exit(EXIT_SUCCESS);
}

void sig_handler2(int num){
    printf("I am SIGINT: %d, counting: %d\n", num, count++);
}

// void sig_handler3(int num){
//     printf("I am SIGTERM: %d, counting: %d\n", num, count++);
// }

int main(){
    if(signal(SIGINT, sig_handler1) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    // signal(SIGKILL, sig_handler2); // Hành động SIGSTOP và SIGKILL là không thể bị catch
    // signal(SIGTERM, sig_handler3);
    // sleep(4);
    // sleep(7);
    // kill(getpid(),SIGINT);

    // printf("process ID: %d\n", getpid());
    while(1){
        // do nothing
        // printf("Autumn\n");
        sleep(2);
    }

    return 0;
}