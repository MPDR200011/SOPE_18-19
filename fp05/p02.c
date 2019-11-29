#include <stdio.h>
#include <pipeline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define BUFFER_SIZE 512

struct input {
    int a;
    int b;
};

struct results {
    int status;
    float sum;
    float sub;
    float mul;
    float div;
};

int main() {
    int parentSend[2];
    int childSend[2];

    if (pipe(parentSend) != 0) {
        perror("parentSend");
        exit(1);
    }
    if (pipe(childSend) != 0) {
        perror("childSend");
        exit(1);
    }

    int childPid = fork();

    if (childPid > 0) {
        close(parentSend[READ]);
        close(childSend[WRITE]);

        struct input input;

        scanf("%d", &input.a);
        scanf("%d", &input.b);

        write(parentSend[WRITE], &input, sizeof(struct input));

        struct results res;

        read(childSend[READ], &res, sizeof(struct results));

        printf("Sum: %f\n", res.sum);
        printf("Sub: %f\n", res.sub);
        printf("Mul: %f\n", res.mul);
        printf("Div: %f\n", res.div);
    } else {
        close(parentSend[WRITE]);
        close(childSend[READ]);

        struct input input;
        struct results res;

        read(parentSend[READ], &input, sizeof(struct input));

        res.status = 0;

        res.sum = input.a + input.b;
        res.sub = input.a - input.b;
        res.mul = input.a * input.b;
        res.div = (float) input.a / input.b;

        write(childSend[WRITE], &res, sizeof(struct results));
    }


    return 0;
}

