#include "stdfoo.h"
#include "vector.h"
#include "msg.h"
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 255

int main(int argc, char* argv[]) {
    int   CurNode     = atoi(argv[1]);
    int   Parentport  = atoi(argv[2]);
    int   size        = -1;
    int   c = 0;
    int   NextNode    = -1;
    void* context     = zmq_ctx_new();
    void* socket      = zmq_socket(context, ZMQ_PULL);
    void* Leftsocket  = zmq_socket(context, ZMQ_PUSH);
    void* Rightsocket = zmq_socket(context, ZMQ_PUSH);
    int   LeftChild   = 0;
    int   RightChild  = 0;
    char* bufferin    = NULL;
    char* bufferout   = NULL;
    char  localhost[21] = "tcp://localhost:";
    vector command;
    vector others;
    vector node;
    vector string;
    vector post;

    AddPort(localhost, Parentport);
    c = zmq_connect(socket, localhost);

    while (1) {
        bufferout = msg_input(&size, socket);
        CreateVec(&command, size);
        CreateVec(&others, size);
        CreateVec(&node, size);
        CreateVec(&string, size);
        CreateVec(&post, size);
        SplitString(command.data, others.data, bufferout);
        // printf("This server: %d\n", CurNode);
        // printf("This server: %s\n", bufferout);
        // printf("This server: %s\n", command.data);
        // printf("This server: %s\n", others.data);
        
        if (!strncmp(command.data, "create", 7)) {
            NextNode = atoi(others.data);
            if (CurNode < NextNode) {
                //RIGHT
                if (RightChild == 0) {
                    if (!create_server(Rightsocket, NextNode))
                        RightChild = 1;
                } else msg_output(size, bufferout, Rightsocket);
            } else if (CurNode > NextNode) {
                //LEFT
                if (LeftChild == 0) {
                    if (!create_server(Leftsocket, NextNode))
                        LeftChild = 1;
                } else msg_output(size, bufferout, Leftsocket);
            } else if (CurNode == NextNode)
                printf("Error: Already exists\n");
        } else if (!strncmp(command.data, "exec", 5)) {
            SplitString(node.data, string.data, others.data);
            NextNode = atoi(node.data);
            if (NextNode < CurNode) {
                //LEFT
                if (LeftChild) 
                    msg_output(size, bufferout, Leftsocket);
                else 
                    printf("Error: %d Not found\n", NextNode);
            } else if (CurNode < NextNode) {
                //RIGHT
                if (RightChild) 
                    msg_output(size, bufferout, Rightsocket);
                else 
                    printf("Error: %d Not found\n", NextNode);       
            } else if (CurNode == NextNode) {
                printf("Ok:%d:", CurNode);
                exec_server(string.data);
            }
        } else if (!strncmp(command.data, "ping", 5)) {
            NextNode = atoi(others.data);
            if (NextNode < CurNode) {
            //LEFT
            if (LeftChild) 
                msg_output(size, bufferout, Leftsocket);
            else 
                printf("Error: %d Not found\n", NextNode);
            } else if (CurNode < NextNode) {
                //RIGHT
                if (RightChild) 
                    msg_output(size, bufferout, Rightsocket);
                else 
                    printf("Error: %d Not found\n", NextNode);
            } else if (NextNode == CurNode) {
                printf("Ok: 1\n");
            }
        }

        DestroyString(bufferout);
        Destroy(&command);
        Destroy(&others);
        Destroy(&node);
        Destroy(&post);
        Destroy(&string);
    }

    zmq_close(socket);
	zmq_ctx_destroy(context);

    return 0;
}