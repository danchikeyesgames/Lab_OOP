#ifndef __MSG_H__
#define __MSG_H__

void    SplitString(char* command, char* other, char* arr);
char*   CreateString(int size);
void    DestroyString(char* str);
char*   msg_input(int* sz, void* socket);
void    msg_output(int size, char* _msg, void* socket);

#endif