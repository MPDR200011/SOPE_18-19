#include <stdio.h>
#include <pipeline.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1
#define BUFFER_SIZE 512

struct data {
    float a;
    float b;
};

int main() {
    int coms[2];

    if (pipe(coms) != 0) {
        perror("pipe");
        exit(1);
    }

    int childPid = fork();

    if (childPid > 0) {
        close(coms[READ]);
    
        struct data numbers;

        scanf("%f", &numbers.a);
        scanf("%f", &numbers.b);

        write(coms[WRITE], &numbers, sizeof(struct data));
    } else {
        close(coms[WRITE]);
        dup2(coms[READ], STDIN_FILENO);

        struct data numbers;

        read(coms[READ], &numbers, sizeof(struct data));

        float sum = numbers.a + numbers.b;
        float sub = numbers.a - numbers.b;
        float mul = numbers.a * numbers.b;
        float div = numbers.a / numbers.b;

        printf("Sum: %f\n", sum);
        printf("Sub: %f\n", sub);
        printf("Mul: %f\n", mul);
        printf("Div: %f\n", div);
    }


    return 0;
}

