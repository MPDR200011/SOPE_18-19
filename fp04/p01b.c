
// PROGRAMA p01a.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    sigset_t mask;
    sigset_t oldMask;
    sigfillset(&mask);

    sigprocmask(SIG_BLOCK, &mask, &oldMask);

    printf("Sleeping for 30 seconds ...\n");
    sleep(30);
    printf("Waking up ...\n");

    sigprocmask(SIG_SETMASK, &oldMask, NULL);

    exit(0);
}
