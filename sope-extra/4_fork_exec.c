#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
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

    printf("%s: [OUT] %s\n", NAME, SIGNAL_STR[signo]);
}

int set_signal_handler(int signo) {
    struct sigaction action;

    action.sa_handler = sig_handler;
    action.sa_flags = 0;

    sigemptyset(&action.sa_mask);

    return sigaction(signo, &action, NULL);
}

int main(int argc, char* argv[]) {
    sigset_t mask, omask;
    int status = 0, ret = 0;
    pid_t pid;

    if (argc == 1) {
        if (set_signal_handler(SIGINT) == -1) {
            perror("sigaction");

            return 1;
        }

        sigemptyset(&mask);
        sigaddset(&mask, SIGINT);

        sigprocmask(SIG_SETMASK, &mask, &omask);

        print_pending_signals();

        switch ((pid = fork())) {
            case -1:
                perror("fork");
                return 2;
            case 0:
                execlp(argv[0], argv[0], "dummy", NULL);
                return 4;
            default:
                break;
        }

        sleep(1);
        kill(-getpgid(getpid()), SIGINT);
    } else {
        if (set_signal_handler(SIGINT) == -1) {
            perror("sigaction");

            return 1;
        }

        sleep(2);
        print_pending_signals();
        sigemptyset(&omask);
        (void)argv;
    }

    print_pending_signals();
    sigprocmask(SIG_SETMASK, &omask, NULL);

    if (is_parent()) {
        ret = wait(&status);

        if (WIFEXITED(status))
            printf("WAIT: %d => %d\n", ret, WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("WAIT (SIGNALED): %d => %d\n", ret, status);
        else
            printf("WAIT (OTHER): %d => %d\n", ret, status);
    }

    return 0;
}
