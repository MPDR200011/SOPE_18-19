#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_LENGTH 256

int main(int argn, char * argv[]) {

  if (argn < 3) {
    printf("usage: program_name inputfile outputfile\n");
    exit(0);
  }

  FILE *src, *dst;
  char buf[BUF_LENGTH];

  if ((src = fopen(argv[1], "r")) == NULL) {
    printf("%d\n", errno);
    exit(1);
  }

  if ((dst = fopen(argv[2], "w")) == NULL) {
    printf("%d\n", errno);
    exit(2);
  }

  while ((fgets(buf, BUF_LENGTH, src)) != NULL) {
      fputs(buf, dst);
  }
  
  fclose(src);
  fclose(dst);
  
  exit(0);  // zero é geralmente indicativo de "sucesso"
}
