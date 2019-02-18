#include <stdio.h>
#include <stdlib.h>

/*
 * Call it like: 
 *    $prog_name "Name" 5.
 * Will print out "Hello Name !" 5 times.
 *
 */
int main(int argn, char * argv[]) {

  for (int i = 0; i < atoi(argv[2]); i++) {
    printf("Hello %s !\n", argv[1]);
  }
  return 0;
}
