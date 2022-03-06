#include <stdio.h>
#include "vector.h"
#include "funcom.h"
#include <stdlib.h>
#include "msg.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    int     NodePid  = 0;
    int     fd_read, fd_write, fd_give, child = 0, count = 1, fd_tmp;
    char    buffer[PIPE_BUF], command[PIPE_BUF], name[PIPE_BUF], other[PIPE_BUF], new_msg[PIPE_BUF];
    char    namefile[PIPE_BUF], namepid[PIPE_BUF], Nameof[PIPE_BUF], Namekyda[PIPE_BUF], messegersd[PIPE_BUF];
    char    namechat[PIPE_BUF], tmpchat[PIPE_BUF], othername[PIPE_BUF], argv1[PIPE_BUF], argv2[PIPE_BUF];
    char    __tmp[PIPE_BUF];
    int     indicator = 0;
    FILE*   corrected;
    char*   h[PIPE_BUF];
    vector_int* __fd_write = NULL;

    if (argc == 1) {
        CreatePipe("file0", 0666);
        printf("Ok\n");
        fd_read = ConnectPipe("file0", O_RDONLY);
        printf("Server set up!\n");

        while (1) {
            memset(buffer, '\0', PIPE_BUF);
            ReadPipe(fd_read, buffer);
            printf("%s\n", buffer);
            if (CorrectWord(buffer))
                SplitString(command, name, buffer);
            else {printf("nocorrected\n"); continue;}

            if (!strncmp("/login", command, 7)) {
                if (!child) {
                    memcpy(namefile, "file", strlen("file"));
                    strncat(namefile, to_string(count), strlen(to_string(count)) + 1);
                    count++;
                    CreatePipe(namefile, 0666);
                    CreateNewServer(namefile, name);
                    fd_give = ConnectPipe(namefile, O_WRONLY);
                    memcpy(Nameof, namefile, PIPE_BUF);
                    child = 1;
                } else {
                    memcpy(namefile, "file", strlen("file"));
                    strncat(namefile, to_string(count), strlen(to_string(count)) + 1);
                    count++;
                    strncat(buffer, " ", 2);
                    strncat(buffer, namefile, strlen(namefile) + 1);
                    write(fd_give, buffer, strlen(buffer));
                }
            } else if (!strncmp("/msg", command, 5)) {
                if (child) {
                    write(fd_give, buffer, strlen(buffer));
                } else {
                    fd_write = ConnectPipe(Nameof, O_RDONLY);
                    write(fd_write, "Server: Not found", strlen("Not found") + 1);
                    close(fd_write);
                }
            } else if (!strncmp("/create", command, 5)) {
                if (child) {
                    write(fd_give, buffer, strlen(buffer));
                } else {
                    fd_write = ConnectPipe(Nameof, O_RDONLY);
                    write(fd_write, "Server: Not found", strlen("Not found") + 1);
                    close(fd_write);
                }
            }

        }
        close(fd_read);
    } else {
        if (argc < 4) {
            fd_read  = ConnectPipe(argv[1], O_RDONLY);
            fd_write = ConnectPipe(argv[2], O_WRONLY);
        } else {
            fd_read  = ConnectPipe(argv[1], O_RDONLY);
            printf("%s startup--> %s\n", argv[1], argv[2]);

            __fd_write = (vector_int *) malloc(sizeof(vector_int));
            CreateVec_int(__fd_write, 2);

            memcpy(tmpchat, argv[2], szof(argv[2]) + 1);
            printf(":%s -- %d\n", tmpchat, szof(argv[2]));
            while (CorrectWord(tmpchat)) {
                printf("tyt1\n");
                SplitString(argv1, argv2, tmpchat);
                printf("%s\n", argv2);
                if (indicator == 0) {
                    memcpy(Nameof, argv1, strlen(argv1) + 1);
                }
                if ((corrected = fopen(argv1, "rw")) != NULL) {
                    if (indicator >= __fd_write->size)
                        Resize_int(__fd_write, __fd_write->size * 2);
                    
                    h[indicator] = (char *) malloc(sizeof(char) * PIPE_BUF);
                    memcpy(h[indicator], argv1, strlen(argv1) + 1);
                    __fd_write->data[indicator] = ConnectPipe(argv1, O_WRONLY);
                    indicator++;
                    memset(tmpchat, '\0', PIPE_BUF);
                    memcpy(tmpchat, argv2, strlen(argv2) + 1);
                    fclose(corrected);
                } else {
                    fd_tmp = ConnectPipe(Nameof, O_WRONLY);
                    printf("Not found\n");
                    memcpy(__tmp, "Server: Not found ", strlen("Server: Not found ") + 1);
                    strncat(__tmp, argv1, strlen(argv1) + 1);
                    write(fd_tmp, __tmp, PIPE_BUF);
                    memset(tmpchat, '\0', PIPE_BUF);
                    memcpy(tmpchat, argv2, strlen(argv2) + 1);
                    close(fd_tmp);
                }
            }
            printf("tyt2\n");
            printf("is %s -- string\n", tmpchat);
            if ((corrected = fopen(argv1, "rw")) != NULL) {
                if (indicator >= __fd_write->size)
                        Resize_int(__fd_write, __fd_write->size * 2);
                h[indicator] = (char *) malloc(sizeof(char) * PIPE_BUF);
                    memcpy(h[indicator], argv1, strlen(argv1) + 1);
                __fd_write->data[indicator] = ConnectPipe(tmpchat, O_WRONLY);
                indicator++;
                printf("tyt\n");
                for (int i = 0; i < indicator; i++)
                    printf("%d ", __fd_write->data[i]);
            } else {
                fd_tmp = ConnectPipe(Nameof, O_WRONLY);
                printf("Not found\n");
                memcpy(__tmp, "Server: Not found ", strlen("Server: Not found ") + 1);
                strncat(__tmp, tmpchat, strlen(tmpchat) + 1);
                write(fd_tmp, __tmp, PIPE_BUF);
                close(fd_tmp);
            }
            memset(Nameof, '\0', PIPE_BUF);
        }

        while (1) {
            memset(buffer, '\0', PIPE_BUF);
            ReadPipe(fd_read, buffer);
            printf("%s\n", buffer);
            if (CorrectWord(buffer))
                SplitString(command, name, buffer);
            else {printf("nocorrected\n"); continue;}

            if (!strncmp("/login", command, 7)) {
                SplitString(namepid, other, name);
                if (!child) {
                    CreatePipe(other, 0666);
                    CreateNewServer(other, namepid);
                    fd_give = ConnectPipe(other, O_WRONLY);
                    child = 1;
                } else {
                    write(fd_give, buffer, strlen(buffer));
                }
            } else if (!strncmp("/msg", command, 5)) {
                SplitString(Namekyda, other, name);
                if (argc < 4) {
                    if (!strncmp(argv[2], Namekyda, strlen(Namekyda) + 1)) {

                        if (CorrectWord(other)) {
                            SplitString(Nameof, messegersd, other);
                            printf("--> %s <--\n", Nameof);
                        } else {
                            printf("No Message!\n");
                            continue;
                        }

                        memcpy(new_msg, "Message: \n", 11);
                        strncat(new_msg, Nameof, strlen(Nameof) + 1);
                        strncat(new_msg, ": ", 3);
                        strncat(new_msg, messegersd, strlen(messegersd) + 1);
                        printf("Message: \n"
                        "%s: %s\n", Nameof, messegersd);
                        write(fd_write, new_msg, PIPE_BUF);
                        memset(new_msg, '\0', PIPE_BUF);
                    } else if (child) {
                        printf("--->\n");
                        write(fd_give, buffer, PIPE_BUF);
                    } else {
                        if (CorrectWord(other)) {
                            SplitString(Nameof, messegersd, other);
                            printf("--> %s <--\n", Nameof);
                        } else {
                            printf("No Message!\n");
                            continue;
                        }
                        printf("Not found %s\n", Nameof);
                        fd_tmp = ConnectPipe(Nameof, O_WRONLY);
                        printf("Not found\n");
                        write(fd_tmp, "Server: Not found\n", PIPE_BUF);
                        close(fd_tmp);
                        memset(Nameof, '\0', PIPE_BUF);
                    }
                } else {
                    if (!strncmp(argv[1], Namekyda, strlen(Namekyda) + 1)) {

                        if (CorrectWord(other))
                            SplitString(Nameof, messegersd, other);
                        else {
                            printf("No Message!\n");
                            continue;
                        }

                        memcpy(new_msg, "Message: \n", 11);
                        strncat(new_msg, argv[1], strlen(argv[1]) + 1);
                        strncat(new_msg, ":", 2);
                        strncat(new_msg, Nameof, strlen(Nameof) + 1);
                        strncat(new_msg, ": ", 3);
                        strncat(new_msg, messegersd, strlen(messegersd) + 1);
                        printf("Message: \n"
                        "%s: %s\n", Nameof, messegersd);
                        for (int i = 0; i < indicator; i++)
                            if (strncmp(h[i], Nameof, strlen(h[i]) + 1))
                                write(__fd_write->data[i], new_msg, PIPE_BUF);
                        memset(new_msg, '\0', PIPE_BUF);
                    } else if (child) {
                        printf("--->\n");
                        write(fd_give, buffer, PIPE_BUF);
                    } else {
                        if (CorrectWord(other)) {
                            SplitString(Nameof, messegersd, other);
                            printf("--> %s <--\n", Nameof);
                        } else {
                            printf("No Message!\n");
                            continue;
                        }
                        printf("Not found %s\n", Nameof);
                        fd_tmp = ConnectPipe(Nameof, O_WRONLY);
                        printf("Not found\n");
                        write(fd_tmp, "Server: Not found\n", PIPE_BUF);
                        close(fd_tmp);
                        memset(Nameof, '\0', PIPE_BUF);
                    }
                }
            } else if (!strncmp("/create", command, 5)) {
                if (!child) {
                    if (CorrectWord(name))
                        SplitString(namechat, othername, name);
                    else {
                        printf("No Message---!\n");
                        continue;
                    }

                    CreatePipe(namechat, 0666);
                    CreateNewChat(namechat, othername);
                    fd_give = ConnectPipe(namechat, O_WRONLY);
                    child = 1;
                } else { 
                    write(fd_give, buffer, PIPE_BUF);
                }
            }

            memset(namechat, '\0', PIPE_BUF);
            memset(tmpchat, '\0', PIPE_BUF);
            memset(othername, '\0', PIPE_BUF);
        }
        close(fd_read);
        close(fd_write);
    }

    return 0;
}