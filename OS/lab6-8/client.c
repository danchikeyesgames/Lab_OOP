#include "stdfoo.h"
#include "msg.h"
#include "vector.h"
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX 15

static void clear(void);

int main(void) {
    int port = 1337;
    char buffer[MAX];
    void* context  = zmq_ctx_new();
    void* socket   = zmq_socket(context, ZMQ_PUSH);
    zmq_bind(socket, "tcp://*:1337");

    while (scanf("%s", buffer) > 0) {
        if (!strncmp(buffer, "create", MAX)) {
            if (!create_client(port, socket))
                port++;
            clear();
        } else if (!strncmp(buffer, "exec", MAX)) {
            exec_client(socket);
        } else if (!strncmp(buffer, "ping", MAX)) {
            ping_client(socket);
            clear();
        } else {
            printf("Error: incorrected format\n");
            clear();
        }
    }
    
    zmq_close(socket);
	zmq_ctx_destroy(context);

    return 0;
}

static void clear(void) {
    char c = getchar();
    while (c != '\0' && c != '\n' && c != EOF)
        c = getchar();
}