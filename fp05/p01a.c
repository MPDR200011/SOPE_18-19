#include <stdio.h>
#include <pipeline.h>
#include <unistd.h>
#include <stdlib.h>

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
        float a;
        scanf("%f", &a);

        float b;
        scanf("%f", &b);
        dup2(coms[WRITE], STDOUT_FILENO);

        printf("%f %f", a, b);

    } else {
        close(coms[WRITE]);
        dup2(coms[READ], STDIN_FILENO);

        float a;
        scanf("%f", &a);

        float b;
        scanf("%f", &b);

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

