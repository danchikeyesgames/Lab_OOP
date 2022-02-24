#include "stdfoo.h"
#include "msg.h"
#include "vector.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <zmq.h>
#include <stdlib.h>

#define M 255
#define C 6

void  AddPort(char* arr, int port) {
    char* end = strchr(arr, '\0');
    char* str = to_string(port);
    for (int i = 0; i < 4; i++)
        *(end + i) = *(str + i);

    *(end + 4) = '\0';
}

int BindSocket(void* socket) {
    int pport = 1337;
    char buffer[20] = "tcp://*:";

    AddPort(buffer, pport);
    int c = zmq_bind(socket, buffer);
    while (c != 0) {
        pport++;
        buffer[8] = '\0';
        AddPort(buffer, pport);
        c = zmq_bind(socket, buffer);
    }

    return pport;
}

int create_client(int port, void* socket) {
    int NodeId;
    int NodePid;
    char bufferout[M];
    char bufferin[M];

    if (scanf("%d", &NodeId) <= 0) {
        printf("Error: incorrected format\n");
        return -1;
    }

    if (port == 1337) {
        NodePid = fork();
        if (NodePid == -1) {
            printf("Error: fail fork()\n");
            return -1;
        } else if (NodePid == 0)
            execl("./server", "server", to_string(NodeId), to_string(port), NULL);
        else printf("Ok: %d\n", NodePid);
    } else {
        zmq_msg_t req;
        memcpy(bufferin, "create ", 8);
        strncat(bufferin, to_string(NodeId), strlen(to_string(NodeId)));
		zmq_msg_init_size(&req, M);
		memcpy(zmq_msg_data(&req), bufferin, strlen(bufferin));
        zmq_msg_send(&req, socket, 0);
		zmq_msg_close(&req);

    }

    return 0;
}

int create_server(void* socket, int _nxNode) {
    int NodePid;
    int port = BindSocket(socket);

    NodePid = fork();
    if (NodePid == -1) {
        printf("Error: fail fork()\n");
        return -1;
    } else if (NodePid == 0)
        execl("./server", "server", to_string(_nxNode), to_string(port), NULL);
    else printf("Ok: %d\n", NodePid);

    return 0;
}

int exec_client(void* socket) {
    int    NodeId  = -1;
    char*  idstr = NULL;
    vector* string = (vector *) malloc(sizeof(vector));
    vector command;

    if (scanf("%d", &NodeId) <= 0) {
        printf("Error: expected a number\n");
        return -1;
    }

    idstr = to_string(NodeId);
    string = s_gets(string);
    CreateVec(&command, C + strlen(idstr) + string->size);
    memcpy(command.data, "exec ", strlen("exec ") + 1);
    strncat(command.data, idstr, strlen(idstr) + 1);
    strncat(command.data, string->data, string->size);
    msg_output(command.size + 1, command.data, socket);

    free(idstr);
    Destroy(&command);
    Destroy(string);
    free(string);
}

void exec_server(char* string) {
    char*   str       = NULL;
    char*   pattern   = NULL;
    vector_int* result    = NULL;
    int i = 0;

    str     = CreateString(strlen(string) + 1);
    pattern = CreateString(strlen(string) + 1);
    SplitString(str, pattern, string);
    result = AlgBM(str, pattern);
    if (!result)
        printf("-1\n");
    else {
        printf("%d", Load_int(result, i));
        i++;
        while (result->size > i) {
            printf(";%d", Load_int(result, i));
            i++;
        }
        putchar('\n');
    }

    DestroyString(str);
    DestroyString(pattern);
}

void ping_client(void* socket) {
    int NodeId, k;
    vector v;
    char* len = NULL;

    scanf("%d", &NodeId);
    CreateVec(&v, M);
    memcpy(v.data, "ping ", 6);
    len = to_string(NodeId);
    strncat(v.data, len, strlen(len));
    msg_output(v.size, v.data, socket);
}

void ping_server(void* socket) {
    int NodeId, k;
    vector v;
    char* len = NULL;

    scanf("%d", &NodeId);
    CreateVec(&v, M);
    memcpy(v.data, "ping ", 6);
    len = to_string(NodeId);
    strncat(v.data, len, strlen(len));
    msg_output(v.size, v.data, socket);
    len = msg_input(&k, socket);
    if (!len)
        printf("Ok: 0\n");
}