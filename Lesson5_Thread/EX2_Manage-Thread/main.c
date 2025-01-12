#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2, thread_id3;

// typedef struct{
//     char name[30];
//     char msg[30];
// } thr_data_t;

static void *thr_handle1(void *args){
    printf("Thread1 handler\n");
    pthread_exit(NULL); // gọi hoặc không gọi cũng kết thúc bằng pthread_exit và kết thúc 1 cách bình thường
}

static void *thr_handle2(void *args){
    // sleep(5);
    while(1){
        printf("Thread2 handler\n");
        sleep(1);
    }
}

static void *thr_handle3(void *args){
    // sleep(2);
    printf("thread3 handler\n");
    pthread_detach(pthread_self()); // ưu tiên sử dụng pp detach hơn join để tránh tạo ra zombie
    // pthread_exit(NULL);
}

int main(int argc, char const *argv[]){
    int ret, counter = 0;
    int retval;
    // thr_data_t data = {0};

    // strncpy(data.name, "Astatine", sizeof(data.name));
    // strncpy(data.msg, "Autumn", sizeof(data.msg));

    if(ret = pthread_create(&thread_id1, NULL, &thr_handle1, NULL)){ //ret = 0 khi thread được tạo thành công; ret != 0 khi xảy ra lỗi
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    sleep(2);

    if(ret = pthread_create(&thread_id2, NULL, &thr_handle2, NULL)){
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    // sleep(5);
    pthread_cancel(thread_id2);
    pthread_join(thread_id2, NULL);
    printf("thread_id2 termination\n");

    // while(1); // thread main phải còn chạy, nếu không thì tất cả các thread khác đều dừng lại

    while(1){
            if(ret = pthread_create(&thread_id3, NULL, &thr_handle3, NULL)){
            printf("pthread_create() error number = %d\n", ret);
            break;
        }
        counter++;
        // pthread_join(thread_id3, NULL); // giúp thread_id3 không trở thành zombie

        if(counter % 1000 == 0){
            printf("thread create: %d\n", counter);
        }
    }

    return 0;
}