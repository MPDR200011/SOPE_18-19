#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <time.h>
#include <unistd.h>

static const int USED_SIGNALS[] = {SIGINT, SIGCHLD, SIGUSR1};
static const char *SIGNAL_STR[] = {[SIGINT] = "SIGINT", [SIGCHLD] = "SIGCHLD", [SIGUSR1] = "SIGUSR1"};

bool is_parent() { return (getpgid(getpid()) == getpid()); }

const char *proc_label() { return (is_parent() ? "PRNT" : "CHLD"); }

void sleep_and_print(unsigned int seconds) {
  printf("%s: waited for, at most, %d second(s)\n", proc_label(), seconds - sleep(seconds));
}

void print_pending_signals() {
  sigset_t mask;

  sigpending(&mask);

  printf("%s: Pending =>", proc_label());

  for (size_t i = 0; i < sizeof(USED_SIGNALS) / sizeof(USED_SIGNALS[0]); ++i)
    printf(" %s=%d", SIGNAL_STR[USED_SIGNALS[i]], sigismember(&mask, USED_SIGNALS[i]));

  printf("\n");
}

void sig_handler(int signo) {
  const char *NAME = (is_parent() ? "PRNT" : "CHLD");

  printf("%s: [IN] %s\n", NAME, SIGNAL_STR[signo]);

  if (is_parent())
    sleep_and_print(2);

  print_pending_signals();

  printf("%s: [OUT] %s\n", NAME, SIGNAL_STR[signo]);
}

int main() {
  struct sigaction action;
  sigset_t mask;
  pid_t pid;

  action.sa_handler = sig_handler;
  action.sa_flags = 0;

  sigemptyset(&action.sa_mask);

  if (sigaction(SIGINT, &action, NULL) == -1) {
    perror("sigaction");

    return 1;
  }

  sigfillset(&mask);
  sigdelset(&mask, SIGINT);

  printf("Hit Ctrl+C...\n");
  
  if ((pid = fork()) == -1) {
    perror("fork");

    return 2;
  }

  print_pending_signals();
  sigsuspend(&mask);

  return 0;
}
