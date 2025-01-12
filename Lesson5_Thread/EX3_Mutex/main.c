#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

int counter = 2; // shared variable/shared resources/global variable

static void *thr_handle1(void *args){
    pthread_mutex_lock(&lock1);
    //critical section
    printf("Thread1 handler, counter: %d\n", ++counter);
    sleep(5);
    pthread_mutex_unlock(&lock1);
}

static void *thr_handle2(void *args){
    pthread_mutex_lock(&lock1);
    //critical section
    printf("Thread2 handler, counter: %d\n", ++counter);
    pthread_mutex_unlock(&lock1);
}

int main(int argc, char const *argv[]){
    /* code */
    int ret;
    pthread_t thread_id1, thread_id2;

    if(ret = pthread_create(&thread_id1, NULL, &thr_handle1, NULL)){ //ret = 0 khi thread được tạo thành công; ret != 0 khi xảy ra lỗi
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    if(ret = pthread_create(&thread_id2, NULL, &thr_handle2, NULL)){
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    // used to block for the end of a thread and release
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    // while(1);

    return 0;
}