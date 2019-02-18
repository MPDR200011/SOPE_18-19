#include <stdio.h>
#include <stdlib.h>

int main(int argn, char * argv[], char * envp[]) {

  char * username = getenv("USER_NAME");

  printf("Hello %s !\n", username);

  return 0;
}
