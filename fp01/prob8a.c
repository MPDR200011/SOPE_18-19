#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argn, char * argv[]) {

  if (argn < 3) {
    return -1;
  }

  int max = atoi(argv[1]);
  int target = atoi(argv[2]);

  srand(time(NULL));
  int guess;
  do {
    guess = rand() % max;
    printf("%d\n", guess);
  } while(guess != target);

  return 0;
}
