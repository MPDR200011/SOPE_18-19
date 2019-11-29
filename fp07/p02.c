#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STDERR 2
#define NUMITER 10000

int counter = 50000;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thrfunc(void* arg) {
    fprintf(stderr, "Starting thread %s\n", (char*)arg);

    int* total = malloc(sizeof(int));
    *total = 0;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (counter <= 0) {
            pthread_mutex_unlock(&mutex);
            return total;
        }
        counter--;
        pthread_mutex_unlock(&mutex);
        write(STDERR, arg, 1);
        (*total)++;
    }
}

int main() {
    pthread_t ta, tb;
    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");

    void * aresult;
    void * bresult;

    pthread_join(ta, &aresult);
    pthread_join(tb, &bresult);

    printf("1 result: %d\n", *(int *)aresult);
    printf("2 result: %d\n", *(int *)bresult);
    printf("Total: %d\n", *(int *)aresult + *(int *)bresult);

    free(aresult);
    free(bresult);

    return 0;
}
