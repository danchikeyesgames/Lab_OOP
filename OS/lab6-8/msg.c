#include "msg.h"
#include "vector.h"
#include <unistd.h>
#include <string.h>
#include <zmq.h>
#include <stdlib.h>

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

char* CreateString(int size) {
    char* push = (char *) malloc(sizeof(char) * size);
    return push;
}

void DestroyString(char* str) {
    free(str);
}

vector* s_gets(vector* string) {
    CreateVec(string, 2);
    char c;
    int i = 0;

    c = getchar();
    Save(string, i, ' ');
    i++;
    c = getchar();
    while (c != '\n' && c != ' ' && c != EOF) {
        if (i >= string->size)
            Resize(string, i * 2);

        Save(string, i, c);
        i++;
        c = getchar();
    }
    
    if (c == EOF)
        return NULL;

    if (i >= string->size)
            Resize(string, i * 2);
    Save(string, i, ' ');
    i++;

    c = getchar();
    while (c != '\n' && c != ' ' && c != EOF) {
        if (i >= string->size)
            Resize(string, i * 2);

        Save(string, i, c);
        i++;
        c = getchar();
    }

    if (c == EOF)
        return NULL;

    if (i >= string->size)
            Resize(string, i * 2);
    Save(string, i, '\0');

    if (c != '\n')
        while(getchar() != '\n')
            continue;

    return string;
}

char* msg_input(int* sz, void* socket) {
    zmq_msg_t reply;
    zmq_msg_init(&reply);
    int k = zmq_msg_recv(&reply, socket, 0);
    if (k == -1)
        printf("Ok: 0\n");
    *sz = strlen(zmq_msg_data(&reply)) + 1;
    char* bufferout = CreateString(*sz);
    memcpy(bufferout, zmq_msg_data(&reply), *sz);
    zmq_msg_close(&reply);
    
    return bufferout;
}

void msg_output(int size, char* _msg, void* socket) {
        zmq_msg_t req;
		zmq_msg_init_size(&req, size);
		memcpy(zmq_msg_data(&req), _msg, size);
        zmq_msg_send(&req, socket, 0);
		zmq_msg_close(&req);
}