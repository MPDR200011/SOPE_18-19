#include <unistd.h>
#include <stdio.h>
#include <termio.h>

int main() {

    struct termios term, oldTerm;

    tcgetattr(STDIN_FILENO, &oldTerm);
    term=oldTerm;
    term.c_lflag &= ~(ECHO | ECHONL | ECHOE | ECHOK | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    size_t PASS_LENGTH = 30;
    size_t i = 0;
    char pass[PASS_LENGTH +1], ch, echo = '*';

    while (i < PASS_LENGTH && read(STDIN_FILENO, &ch, 1) && ch != '\n') {
        pass[i++] = ch;
        write(STDOUT_FILENO, &echo, 1);
    }
    pass[i] = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);

    printf("\n%s\n",pass);

    return 0;
}
