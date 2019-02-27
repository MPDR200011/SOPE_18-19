#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    DIR* dirp;
    struct dirent* direntp;
    struct stat stat_buf;
    char* str;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s dir_name\n", argv[0]);
        exit(1);
    }

    if ((dirp = opendir(argv[1])) == NULL) {
        perror(argv[1]);
        exit(2);
    }

    chdir(argv[1]);

    while ((direntp = readdir(dirp)) != NULL) {
        if (stat(direntp->d_name, &stat_buf) == -1) {
            printf("error in lstat\n");
        }
        if (S_ISREG(stat_buf.st_mode)) {
            str = "regular";
            printf("%-25s - %-15lu - %s - %ld BYTES\n", direntp->d_name, stat_buf.st_ino,
                   str, stat_buf.st_size);
        } else if (S_ISDIR(stat_buf.st_mode)) {
            str = "directory";
            printf("%-25s - %-15lu - %s\n", direntp->d_name, stat_buf.st_ino,
                   str);
        } else if (S_ISLNK(stat_buf.st_mode)) {
            str = "link";
            printf("%-25s - %-15lu - %s\n", direntp->d_name, stat_buf.st_ino,
                   str);
        } else {
            str = "other";
            printf("%-25s - %-15lu - %s\n", direntp->d_name, stat_buf.st_ino,
                   str);
        }
    }

    closedir(dirp);
    exit(0);
}
