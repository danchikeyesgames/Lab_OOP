#include <stdio.h>
#include <string.h>
#include "msg.h"
#include "vector.h"
#include "funcom.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

int main(void) {
    int     fd_write, fd_read;
    char    buffer[PIPE_BUF], command[PIPE_BUF], name[PIPE_BUF], other[PIPE_BUF], tmp[PIPE_BUF], NodeName[PIPE_BUF], msg[PIPE_BUF];
    char    namechat[PIPE_BUF], tmpchat[PIPE_BUF], othername[PIPE_BUF];
    char*   bufin; char* msgin; char* newstr;
    vector* cmd;

    fd_write = ConnectPipe("file0", O_WRONLY);
    printf("Connected in server\n");

    while(1) {
        printf("Login: ");
        cmd = s_gets();
        printf("--------------------\n");
        printf("%s\n", cmd->data);
        
        memcpy(buffer, cmd->data, strlen(cmd->data) + 1);
        if (CorrectWord(buffer)) {
            SplitString(command, name, buffer);
        } else {printf("Error: pls log in\n"); Destroy(cmd); continue;}

        if (!strncmp(command, "login", 6)) {
            memcpy(tmp, "/", 2);
            strncat(tmp, buffer, strlen(buffer) + 1);
            CreateFork(name);
            memcpy(NodeName, name, strlen(name) + 1);
            write(fd_write, tmp, PIPE_BUF);
            Destroy(cmd);
            break;
        } else {printf("Error: pls log in\n"); Destroy(cmd); continue;}

        Destroy(cmd);
    }

    while (1) {
        cmd = s_gets();

        memcpy(buffer, cmd->data, strlen(cmd->data) + 1);
        if (CorrectWord(buffer)) {
            SplitString(command, name, buffer);
        } else {printf("Incorrected command\n"); Destroy(cmd); continue;}

        if (!strncmp(command, "msg", 4)) {
            memcpy(tmp, "/", 2);
            strncat(tmp, buffer, strlen(buffer) + 1);
            strncat(tmp, " ", 2);
            strncat(tmp, NodeName, strlen(NodeName) + 1);
            printf("Message: ");
            strncat(tmp, " ", 2);
            msgin = fgets(msg, PIPE_BUF, stdin);
            newstr = strchr(msgin, '\n');
            *newstr = '\0';
            printf("--------------------\n");
            strncat(tmp, msgin, strlen(msgin) + 1);
            write(fd_write, tmp, PIPE_BUF);
        } else if (!strncmp(command, "create", 7)) {
            msgin = fgets(msg, PIPE_BUF, stdin);
            newstr = strchr(msgin, '\n');
            *newstr = '\0';

            memcpy(tmp, "/", 2);
            strncat(tmp, buffer, strlen(buffer) + 1);
            strncat(tmp, " ", 2);
            strncat(tmp, NodeName, strlen(NodeName) + 1);
            strncat(tmp, " ", 2);
            strncat(tmp, msgin, strlen(msgin) + 1);
            write(fd_write, tmp, PIPE_BUF);
        } else {printf("--------------------\n"); printf("Incorrected command\n"); Destroy(cmd); continue;}

        memset(buffer, '\0', PIPE_BUF);
        memset(namechat, '\0', PIPE_BUF);
        memset(tmpchat, '\0', PIPE_BUF);
        memset(othername, '\0', PIPE_BUF);
        memset(name, '\0', PIPE_BUF);
        memset(tmp, '\0', PIPE_BUF);
        Destroy(cmd);
    }

    return 0;
}