#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADNUM 50

void* threadFunc(void* arg) {
    sleep(1);
    printf("%lu\n", pthread_self());
    return arg;
}

int main(void) {
    pthread_t threads[THREADNUM];
    int params[THREADNUM];

    for (int i = 0; i < THREADNUM; i++) {
        params[i] = i + 1;
        pthread_create(&threads[i], NULL, threadFunc, &params[i]);
    }

    int* results[THREADNUM];
    for (int i = 0; i < THREADNUM; i++) {
        pthread_join(threads[i], (void**)&results[i]);
    }

    for (int i = 0; i < THREADNUM; i++) {
        printf("Thread %lu : %d\n", threads[i], *results[i]);
    }

    pthread_exit(0);
}
