// PROGRAMA p02a.c
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signo) {
    printf("Entering SIGINT handler ...\n");
    sleep(10);
    printf("Exiting SIGINT handler ...\n");
}

void sigterm_handler(int signo) {
    printf("Entering SIGTERM handler ...\n");
    sleep(10);
    printf("Exiting SIGTERM handler ...\n");
}

int main(void) {
    struct sigaction INTaction;
    INTaction.sa_handler = sigint_handler;
    sigemptyset(&INTaction.sa_mask);
    INTaction.sa_flags = 0;

    struct sigaction TERMaction;
    TERMaction.sa_handler = sigterm_handler;
    TERMaction.sa_flags = 0;
    sigemptyset(&TERMaction.sa_mask);

    if (sigaction(SIGINT, &INTaction, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGINT handler\n");
        exit(1);
    }

    if (sigaction(SIGTERM, &TERMaction, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGTERM handler\n");
        exit(1);
    }

    printf("Try me with CTRL-C ...\n");

    while (1)
        pause();

    exit(0);
}
