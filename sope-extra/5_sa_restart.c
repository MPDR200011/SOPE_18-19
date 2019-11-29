#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static const int USED_SIGNALS[] = {SIGINT, SIGCHLD, SIGUSR1};
static const char* SIGNAL_STR[] = {[SIGINT] = "SIGINT",
                                   [SIGCHLD] = "SIGCHLD",
                                   [SIGUSR1] = "SIGUSR1"};

bool is_parent() {
    return (getpgid(getpid()) == getpid());
}

const char* proc_label() {
    return (is_parent() ? "PRNT" : "CHLD");
}

void sleep_and_print(unsigned int seconds) {
    printf("%s: waited for, at most, %d second(s)\n", proc_label(),
           seconds - sleep(seconds));
}

void print_pending_signals() {
    sigset_t mask;

    sigpending(&mask);

    printf("%s: Pending =>", proc_label());

    for (size_t i = 0; i < sizeof(USED_SIGNALS) / sizeof(USED_SIGNALS[0]); ++i)
        printf(" %s=%d", SIGNAL_STR[USED_SIGNALS[i]],
               sigismember(&mask, USED_SIGNALS[i]));

    printf("\n");
}

void sig_handler(int signo) {
    const char* NAME = (is_parent() ? "PRNT" : "CHLD");

    printf("%s: [IN] %s\n", NAME, SIGNAL_STR[signo]);

    if (is_parent())
        sleep_and_print(2);

    print_pending_signals();

    // raise(signo);

    printf("%s: [OUT] %s\n", NAME, SIGNAL_STR[signo]);
}

#define BUF_SIZE 512

int main(void) {
    struct sigaction action;
    char buf[BUF_SIZE];

    action.sa_handler = sig_handler;
    // action.sa_flags = 0;
    action.sa_flags = SA_RESTART;

    sigemptyset(&action.sa_mask);

    if (sigaction(SIGINT, &action, NULL) == -1) {
        perror("sigaction");

        return 1;
    }

    print_pending_signals();

    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));

    printf("N: %ld, errno=%d [%s]\n", n, errno, strerror(errno));

    return 0;
}
