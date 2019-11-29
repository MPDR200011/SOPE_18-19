#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int v = 0;
static int growth = 1;

void sigusr_handler(int signo) {
    if (signo == SIGUSR1) {
        growth = 1;
    } else if (signo == SIGUSR2) {
        growth = -1;
    }
}

int main() {
    struct sigaction usr1;
    usr1.sa_handler = sigusr_handler;
    sigemptyset(&usr1.sa_mask);
    usr1.sa_flags = 0;

    struct sigaction usr2;
    usr2.sa_handler = sigusr_handler;
    sigemptyset(&usr2.sa_mask);
    usr2.sa_flags = 0;

    if (sigaction(SIGUSR1, &usr1, NULL) < 0) {
        perror("Couldn't set USR1 handler.");
        exit(1);
    }
    if (sigaction(SIGUSR2, &usr2, NULL) < 0) {
        perror("Couldn't set USR2 handler.");
        exit(1);
    }

    while (1) {
        printf("%d\n", v);
        v += growth;
        sleep(1);
    }

    return 0;
}
