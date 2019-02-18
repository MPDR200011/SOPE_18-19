
#include <stdio.h>

/*
 * Call it like prog_name "Name".
 * Will print out "Hello Name !"
 *
 */
int main(int argn, char * argv[]) {

  printf("Hello %s !\n", argv[1]);
  return 0;
}
