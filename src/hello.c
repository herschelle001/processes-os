#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int id, a1, a2, a3, a4;
    char section;

    for(int i=0; i < argc; i++) {
        char *token = strtok(argv[i], " ");

        id = atoi(token);
        token = strtok(NULL, " ");

        section = *token;
        token = strtok(NULL, " ");

        if(section == 'A') {
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
        else {
            break;
        }
    }
    printf("\nChild process finished\n\n");
    return 0;
}