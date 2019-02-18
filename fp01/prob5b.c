#include <stdio.h>
#include <string.h>

int main(int argn, char * argv[], char * envp[]) {

  int i = 0;
  while (envp[i] != NULL) {
    if (strncmp("USER=", envp[i],5) == 0){
      break;
    }
    i++;
  }

  //Since the the USER variable is like this: USER=user_name,
  //the user name starts at index 5 of the variable string.
  printf("Hello %s !\n", envp[i]+5);

  return 0;
}
