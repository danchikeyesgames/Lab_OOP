#include "vector.h"
#ifndef __MSG_H__
#define __MSG_H__

void        CreatePipe(char* name, unsigned int user);
int         ConnectPipe(char* name, int mode);
vector*     s_gets(void);
void        SplitString(char* command, char* other, char* arr);
int         CorrectWord(char* string);
void        ReadPipe(int __fd, char* buf);

#endif