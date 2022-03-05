#include "msg.h"
#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

void CreatePipe(char* name, unsigned int user) {
    unlink(name);
    if (mkfifo(name, (mode_t) user)) {
        perror("mkfifo error:");
        exit(EXIT_FAILURE);
    }
}

int ConnectPipe(char* name, int mode) {
    int fd_info;

    while ((fd_info = open(name, mode, 0)) == -1)
        continue;

    return fd_info;
}

static void clear(void) {
    char c = getchar();
    while (c != '\n' && c != '\0' && c != EOF)
        c = getchar();
}

vector* s_gets(void) {
    vector* tmp = (vector *) malloc(sizeof(vector));
    CreateVec(tmp, 2);
    char c;
    int i = 0;

    c = getchar();
    while (c != ' ' && c != '\n') {
        if (i >= tmp->size)
            Resize(tmp, tmp->size * 2);
        Save(tmp, i, c);
        i++;
        c = getchar();
    }
    if (i >= tmp->size)
            Resize(tmp, tmp->size * 2);
    Save(tmp, i, c);
    i++;

    c = getchar();
    while (c != ' ' && c != '\n') {
        if (i >= tmp->size)
            Resize(tmp, tmp->size * 2);
        Save(tmp, i, c);
        i++;
        c = getchar();
    }

    if (c == ' ')
        clear();

    if (i >= tmp->size)
            Resize(tmp, tmp->size * 2);
    Save(tmp, i, '\0');
    i++;

    tmp->size = i;

    return tmp;
}

void  SplitString(char* command, char* other, char* arr) {
    char* start = arr;
    char* space = strchr(arr, ' ');
    char* end   = strchr(arr, '\0');

    memcpy(command, arr, space - start);
    int diff = space - start;
    *(command + diff) = '\0';

    while (*space == ' ')
        space++;
    memcpy(other, space, end - space + 1);
}

int CorrectWord(char* string) {
    char* chng = strchr(string, ' ');

    return chng ? 1 : 0;
}

void ReadPipe(int __fd, char* buf) {
    while (read(__fd, buf, PIPE_BUF) <= 0)
        continue;
}