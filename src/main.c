#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

extern int errno;

int main () {
    char *lines[1000];              // array of char pointers to store each line of csv file

    int fd, index;
    char *c = (char *) calloc(1, sizeof(char));         // allocate memory to c

    // open and read csv file
    fd = open("csv-os.csv", O_RDONLY);
    index = read(fd, c, 10000);

    // if error occurred print error and exit
    if(index == -1) {
        printf("%s\n", strerror(errno));
        exit(errno);
    }
    c[index] = '\0';

    // get first line
    char *line = strtok(c, "\n");       // discard first line
    line = strtok(NULL, "\n");          // second line

    // store in array declared at line 10
    int size=0;
    while (line) {
        lines[size++] = line;
        line = strtok(NULL, "\n");
    }
    lines[size] = NULL;


    int f = fork();
    // fork failed
    if(f < 0) {
        printf("%s\n", strerror(errno));
        exit(errno);
    }
    // child process
    else if(f == 0) {
        execvp("./hello", lines);       // execute hello.c
        printf("%s\n", strerror(errno));        // if fails then print error and exit
        exit(errno);
    }
    // parent process
    else {
        wait(NULL);
        int id, a1, a2, a3, a4;
        char section;

        for(int i=0; i < size; i++) {
            char *token = strtok(lines[i], " ");        // breaking i-th line into tokens

            id = atoi(token);
            token = strtok(NULL, " ");

            section = *token;
            token = strtok(NULL, " ");

            if (section == 'B') {
                a1 = atoi(token);
                token = strtok(NULL, " ");

                a2 = atoi(token);
                token = strtok(NULL, " ");

                a3 = atoi(token);
                token = strtok(NULL, " ");

                a4 = atoi(token);

                double avg = ((double) a1 + a2 + a3 + a4) / 4;
                printf("Id: %d, section: %c, average: %.2f\n", id, section, avg);
            }
        }
        printf("\nParent process finished\n\n");
    }
    return 0;
}