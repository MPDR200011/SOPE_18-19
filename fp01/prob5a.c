#include <stdio.h>
#include <stdlib.h>

int main(int argn, char * argv[], char * envp[]) {

  int i = 0;
  while (envp[i] != NULL) {
    printf("%s\n", envp[i]);
    i++;
  }

  return 0;
}
