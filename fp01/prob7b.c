#include <stdlib.h>
#include <stdio.h>

void handler1() {
  printf("Executing exit handler 1. \n");
}

void handler2() {
  printf("Executing exit handler 2. \n");
}

/*
 * 1) It is possible to register the same handler more than one time.
 * 2) Calling abort() before de printf call in main abort the program and doesn't run anymore of its code.
 * 3) Calling exit() in a handler runs the exit function once more, creating another stackframe for it self.
 * This makes it run the rest of the handlers that still haven't been run, but the program will return the code given
 * to exit on the first time i t was called.
 */

int main() {

  atexit(&handler1);
  atexit(&handler2);

  printf("Main done! \n");

  return 0;
}
