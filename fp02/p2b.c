#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argn, char * argv[]) {
    if (argn < 3) {
        printf("usage: %s <source> <destination>\n", argv[0]);
        return 0;
    }

    int input, output;

    if ((input = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        exit(1);
    }

    if ((output = open(argv[2], O_WRONLY | O_APPEND)) < 0) {
        perror(argv[2]);
        exit(2);
    }

    size_t size;
    size_t BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE + 1];
    while ((size = read(input, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, size);
        write(output, buffer, size);
    }

    close(input);
    close(output);
}
