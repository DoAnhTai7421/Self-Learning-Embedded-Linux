#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

typedef struct{
    char name[30];
    char msg[30];
} thr_data_t;

static void *thr_handle(void *args){
    // printf("\nHi, I'm thread handle 1\n");

    pthread_t tid = pthread_self();  // pthread_self() trả về ID Thread đang chạy
    thr_data_t *data = (thr_data_t*)args;

    if(pthread_equal(tid, thread_id2)){ // pthread_equal() trả về 1 nếu giống nhau, về 0 nếu khác nhau
        printf("I'm thread_id2\n");
    }else{
        printf("I'm thread_id1\n");
        printf("Hello %s, welcome to join %s\n", data->name, data->msg);
    }
}

static void *thr_handle2(void *args){
    printf("\nHi, I'm thread handle 2\n");
}

int main(int argc, char const *argv[]){
    int ret;
    thr_data_t data = {0};

    strncpy(data.name, "Astatine", sizeof(data.name));
    strncpy(data.msg, "Autumn", sizeof(data.msg));

    if(ret = pthread_create(&thread_id1, NULL, &thr_handle, &data)){ //ret = 0 khi thread được tạo thành công; ret != 0 khi xảy ra lỗi
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    sleep(2);

    if(ret = pthread_create(&thread_id2, NULL, &thr_handle, NULL)){
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    sleep(4);

    return 0;
}