c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Hàm được thực thi bởi mỗi thread
void* print_message(void* threadid) {
    long tid = (long)threadid;
    printf("Thread ID: %ld - Hello Linux!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int rc;
    long t;

    for(t = 0; t < 3; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message, (void*)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Join các thread để đảm bảo tất cả các thread kết thúc trước khi main kết thúc
    for(t = 0; t < 3; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("Main program completed.\n");
    return 0;
}
