#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define NAME_SIZE 50

struct aluno {
    char name[NAME_SIZE + 1];
    int grade;
};

int main() {

    char buffer[NAME_SIZE + 1];

    int outFile = open("notas.txt", O_WRONLY | O_CREAT, 0754);

    char * readResult;
    while (1) {
        struct aluno al;
        readResult = fgets(buffer, NAME_SIZE, stdin);
        if (readResult == 0) {
            break;
        }

        strcpy(&al.name[0], buffer);

        readResult = fgets(buffer, NAME_SIZE, stdin);
        if (readResult == 0) {
            break;
        }
        al.grade = atoi(buffer);

        write(outFile, &al, sizeof(al));
    }

    close(outFile);

    return 0;
}
