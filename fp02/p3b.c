#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argn, char * argv[]) {

    if (argn < 2) {
        printf("usage: %s <filename>\n", argv[0]);
        exit(0);
    }

    int input = open(argv[1], O_RDONLY);
    if (input < 0) {
        perror(argv[1]);
        exit(1);
    }

    int output;
    if (argn > 2) {
        output = open(argv[2], O_WRONLY | O_APPEND);
        if (output < 0) {
            perror(argv[2]);
            exit(2);
        } else {
            dup2(output, STDOUT_FILENO);
        }
    }

    size_t BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE + 1];
    size_t readBytes = 0;
    while ((readBytes = read(input, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, readBytes);
    }

    close(input);

    return 0;
}
