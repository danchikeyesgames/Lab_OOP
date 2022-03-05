#ifndef __FUNCIM_H__
#define __FUNCIM_H__

int CreateNewServer(char* namefile, char* pipename);
int CreateNewChat(char* namefile, char* pipename);
void CreateFork(char* name);
unsigned long szof(char* string);

#endif