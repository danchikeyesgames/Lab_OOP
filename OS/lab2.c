#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX 255

char * WorkProc(char * name, char * newstring);
char * gets_s(char * begin, int max); // svoyz realizaciya gets()
int checker(char x);

int main(void) {
    
    char string[MAX];
    char string1[MAX];
    char string2[MAX];
    char * str = NULL;
    int num = 0, exitfromprog = 1;
    int pipefd1[2], pipefd2[2];

    if (pipe(pipefd1) < 0 || pipe(pipefd2) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child1 = fork();

    if (child1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1) {                    
        pid_t child2 = fork();

        if (child2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (!child2) {                // child2
            close(pipefd2[1]);
            char name[MAX];
            read(pipefd2[0], name, MAX);
            while (1) {

                char newstring[MAX];
                printf("WORK 2\n");
                read(pipefd2[0], newstring, MAX);
                WorkProc(name, newstring);
                printf("WORK 2 (finished)\n");
            }

        } else {                      // parent
            
            printf("Enter filename for child1:\n");
            gets_s(string1, MAX);
            printf("Enter filename for child2:\n");
            gets_s(string2, MAX);
            write(pipefd1[1], string1, MAX);
            write(pipefd2[1], string2, MAX);

            while(1) {

                srand(time(NULL));
                num = rand() % 100 + 1;

                gets_s(string, MAX);
                str = strchr(string, '\0');
                *str = '\n';

                printf("%s", string);

                if (num >= 1 && num <= 80) {
                        printf("work 1 process\n");
                        write(pipefd1[1], string, MAX);

                } else {
                        printf("work 2 process\n");
                        write(pipefd2[1], string, MAX);
                }
            }
            
        }

    } else if (!child1) {             // child1
        close(pipefd1[1]);
        char name[MAX];
        read(pipefd1[0], name, MAX);

        while(1) {
            printf("WORK 1\n");
            char newstring[MAX];
            read(pipefd1[0], newstring, MAX);
            WorkProc(name, newstring);

            printf("WORK 1 (finished)\n");
        }
    }






    return 0;
}

char * gets_s(char * begin, int max) {

    char * start = NULL;
    char tmp[max];
    char * sym;

    start = fgets(tmp, max, stdin);

    if (start) {
        sym = strchr(tmp, '\n');

        if (sym) {
            *sym = '\0';
        } else {
            *(sym + max - 1) = '\0';
        }

        strncpy(begin, tmp, max);
    } else
        exit(EXIT_FAILURE);

    return begin;
}

char * WorkProc(char * name, char * newstring) {

    FILE * file = fopen(name, "a+");

    char sym;

    while ((sym = *newstring) != '\n' && (sym = *newstring) != '\0') {

        if (!checker(sym)) {
            putc(sym, file);
            putchar(sym);
        }
        newstring++;
    }

    putc('\n', file);
    putchar('\n');

    fclose(file);

}

int checker(char x) {
    x = tolower(x);
    if (x == 'a' || x == 'e' || x == 'y' || x == 'u' || x == 'o') {
        return 1;
    } else 
        return 0;
}