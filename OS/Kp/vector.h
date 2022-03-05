#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct _vector {
    int size;
    char* data;
} vector;

typedef struct _vector_int {
    int size;
    int* data;
} vector_int;

void        CreateVec(vector* v, int sz);
int         Empty(vector* v);
char        Load(vector* v, int i);
void        Save(vector* v, int i, char ch);
void        Resize(vector* v, int sz);
void        Destroy(vector* v);
void        CopyVec(vector* src, vector* out, int size);
char*       to_string(int number);
void        CreateVec_int(vector_int* v, int sz);
int         Empty_int(vector_int* v);
int         Load_int(vector_int* v, int i);
void        Resize_int(vector_int* v, int sz);
void        Save_int(vector_int* v, int i, int ch);
void        Destroy_int(vector_int* v);

#endif