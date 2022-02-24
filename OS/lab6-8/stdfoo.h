#ifndef __STDFOO_H__
#define __STDFOO_H__

int   create_client(int port, void* socket);
int   BindSocket(void* socket);
void  AddPort(char* arr, int port);
int   create_server(void* socket, int _nxNode);
int   exec_client(void* socket);
void  exec_server(char* string);
void  ping_server(void* socket);
void  ping_client(void* socket);

#endif