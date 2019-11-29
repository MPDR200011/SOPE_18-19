#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

static int v = 0;
static int growth = 1;
static int childRunning;

void sigusr_handler(int signo) {
    if (signo == SIGUSR1) {
        growth = 1;
    } else if (signo == SIGUSR2) {
        growth = -1;
    }
}

void sigchld_handler(int signo) {
    childRunning = 0;
}

int main() {
    int childPid = fork();
    if (childPid > 0) {
        struct sigaction chld;
        chld.sa_handler = sigchld_handler;
        sigemptyset(&chld.sa_mask);
        chld.sa_flags = 0;

        if (sigaction(SIGCHLD, &chld, NULL) < 0) {
            perror("Couldn't set CHLD handler.");
            kill(childPid, SIGTERM);
            exit(1);
        }

        childRunning = 1;
        while (childRunning) {
            sleep(5);
            int choice = rand() % 2;
            if (choice > 0) {
                kill(childPid, SIGUSR1);
            } else {
                kill(childPid, SIGUSR2);
            }
        }
    } else {
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

        for (int i = 0; i < 50; i++) {
            printf("%d\n", v);
            v += growth;
            sleep(1);
        }
    }

    waitpid(childPid, NULL, 0);

    return 0;
}
