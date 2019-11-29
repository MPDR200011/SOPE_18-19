#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADNUM 50

void * threadFunc(void * arg) {
    sleep(1);
    printf("%lu\n", pthread_self());
    return arg;
}

int main(void) {
    pthread_t threads[THREADNUM];
    int params[THREADNUM];

    for (int i = 1; i <= THREADNUM; i++) {
        params[i] = i;
        pthread_create(&threads[i], NULL, threadFunc, &params[i]);
    }

    pthread_exit(0);
}
