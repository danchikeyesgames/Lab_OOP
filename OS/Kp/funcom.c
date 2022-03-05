#include "funcom.h"
#include <stdio.h>
#include <stdlib.h>
#include "msg.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

int CreateNewServer(char* namefile, char* pipename) {
    int NodePid;

    NodePid = fork();
    if (NodePid == -1) {
        printf("Error: fail fork()\n");
        return -1;
    } else if (NodePid == 0)
        execl("./server", "server", namefile, pipename, NULL);
    else printf("Ok: %d\n", NodePid);
    printf("--------------------\n");

    return 0;
}

int CreateNewChat(char* namefile, char* pipename) {
    int NodePid;

    NodePid = fork();
    if (NodePid == -1) {
        printf("Error: fail fork()\n");
        return -1;
    } else if (NodePid == 0)
        execl("./server", "server", namefile, pipename, "-f", NULL);
    else printf("Ok: %d\n", NodePid);
    printf("--------------------\n");

    return 0;
}

void CreateFork(char* name) {
    int  NodePid, fd_read;
    char buffer[PIPE_BUF];

    NodePid = fork();
    if (NodePid == -1) {
        printf("Error: fail fork()\n");
        return;
    } else if (NodePid == 0) {
        CreatePipe(name, 0666);
        fd_read = ConnectPipe(name, O_RDONLY);

        while(1) {
            ReadPipe(fd_read, buffer);
            printf("%s\n", buffer);
        }
    } //else printf("Ok: %d\n", NodePid);
}

unsigned long szof(char* string) {
    unsigned long i = 0;
    char* start = string;

    while (*start != '\0') {
        start++;
        i++;
    }

    return i;
}