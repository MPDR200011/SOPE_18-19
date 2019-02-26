#include <stdio.h>
#include <stdlib.h>

int main(int argn, char * argv[]) {
    if (argn < 3) {
        printf("usage: %s <source> <destination>\n", argv[0]);
        return 0;
    }

    FILE * input, * output;

    if ((input = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }

    if ((output = fopen(argv[2], "a")) == NULL) {
        perror(argv[2]);
        exit(2);
    }

    size_t size;
    size_t BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE + 1];
    while ((size = fread(buffer, 1, BUFFER_SIZE, input)) > 0) {
        fwrite(buffer, 1, size, stdout);
        fwrite(buffer, 1, size, output);
    }

    fclose(input);
    fclose(output);
}
