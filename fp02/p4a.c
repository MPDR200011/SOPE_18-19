#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {

    size_t NAME_SIZE = 50;
    char buffer[NAME_SIZE + 1];

    int outFile = open("notas.txt", O_WRONLY | O_CREAT, 0754);

    char * readResult;
    while (1) {
        readResult = fgets(buffer, NAME_SIZE+1, stdin);
        if (readResult == 0) {
            break;
        }
        write(outFile, buffer, strlen(buffer));

        readResult = fgets(buffer, NAME_SIZE+1, stdin);
        if (readResult == 0) {
            break;
        }
        write(outFile, buffer, strlen(buffer));
    }

    close(outFile);

    return 0;
}
