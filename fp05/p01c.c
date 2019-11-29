#include <stdio.h>
#include <pipeline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define BUFFER_SIZE 512

int main() {
    int coms[2];

    if (pipe(coms) != 0) {
        perror("pipe");
        exit(1);
    }

    int childPid = fork();

    if (childPid > 0) {
        close(coms[READ]);

        char firstNumber[BUFFER_SIZE];
        char secondNumber[BUFFER_SIZE];

        read(STDIN_FILENO, firstNumber, BUFFER_SIZE);
        read(STDIN_FILENO, secondNumber, BUFFER_SIZE);

        write(coms[WRITE], firstNumber, BUFFER_SIZE);
        write(coms[WRITE], secondNumber, BUFFER_SIZE);
    } else {
        close(coms[WRITE]);
        dup2(coms[READ], STDIN_FILENO);

        char firstNumber[BUFFER_SIZE];
        char secondNumber[BUFFER_SIZE];
        
        read(coms[READ], firstNumber, BUFFER_SIZE);
        read(coms[READ], secondNumber, BUFFER_SIZE);

        float a = atof(firstNumber);
        float b = atof(secondNumber);

        float sum = a + b;
        float sub = a - b;
        float mul = a * b;
        float div = a / b;

        printf("Sum: %f\n", sum);
        printf("Sub: %f\n", sub);
        printf("Mul: %f\n", mul);
        printf("Div: %f\n", div);
    }


    return 0;
}

