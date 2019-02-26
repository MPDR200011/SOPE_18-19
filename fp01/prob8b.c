#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

int main(int argn, char* argv[]) {
  struct tms start, end;

  if (argn < 3) {
    return -1;
  }

  clock_t startT = clock();
  times(&start);

  int max = atoi(argv[1]);
  int target = atoi(argv[2]);

  srand(time(NULL));
  int guess;
  do {
    guess = rand() % max;
    printf("%d\n", guess);
  } while (guess != target);

  clock_t endT = clock();
  times(&end);
  double ticks_sec = (double)sysconf(_SC_CLK_TCK);

  printf("Real time: %lf\n", (double)(endT - startT) / CLOCKS_PER_SEC);
  printf("CPU user: %lf\n", (end.tms_utime - start.tms_utime) / ticks_sec);
  printf("CPU system: %lf\n", (end.tms_stime - start.tms_stime) / ticks_sec);

  return 0;
}
