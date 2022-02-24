#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void CreateVec(vector* v, int sz) {
    v->size = sz;
    v->data = (char *) malloc(sizeof(char) * sz);
}

int  Empty(vector* v) {
    return v->size == 0 ? 1 : 0;
}

char  Load(vector* v, int i) {
    return (i >= 0 && i < v->size) ? v->data[i] : -1;
}

void Resize(vector* v, int sz) {
    v->data = (char *) realloc(v->data, sizeof(char) * sz);
    v->size = sz;
}

void Save(vector* v, int i, char ch) {
    i >= 0 && i < v->size ? v->data[i] = ch : 0;
}

void Destroy(vector* v) {
    v->size = 0;
    free(v->data);
}

void CreateVec_int(vector_int* v, int sz) {
    v->size = sz;
    v->data = (int *) malloc(sizeof(int) * sz);
}

int  Empty_int(vector_int* v) {
    return v->size == 0 ? 1 : 0;
}

int  Load_int(vector_int* v, int i) {
    return (i >= 0 && i < v->size) ? v->data[i] : -1;
}

void Resize_int(vector_int* v, int sz) {
    v->data = (int *) realloc(v->data, sizeof(int) * sz);
    v->size = sz;
}

void Save_int(vector_int* v, int i, int ch) {
    i >= 0 && i < v->size ? v->data[i] = ch : 0;
}

void Destroy_int(vector_int* v) {
    v->size = 0;
    free(v->data);
}

void CopyVec(vector* src, vector* out, int size) {
    char tmp = -1;
    int i = 0;
    int j = size;
    
    CreateVec(out, size);
    tmp = Load(src, j);

    while (!isdigit(tmp)) {
        j--;
        tmp = Load(src, j);
    }

    while (j >= 0) {
        tmp = Load(src, j);
        Save(out, i, tmp);
        j--;
        i++;
    }

    Save(out, i, '\0');
}

char* to_string(int number) {
    vector str;
    vector new;
    int tmp, i = 0;
    char ch;
    CreateVec(&str, 2);

    if (!number) {
        Save(&str, i, '0');
        i++;
    }

    while (number) {
        tmp = number % 10;
        ch = tmp + 48;
        if (i >= str.size)
            Resize(&str, str.size * 2);
        Save(&str, i, ch);
        number /= 10;
        i++;
    }

    if (i >= str.size)
            Resize(&str, str.size * 2);
    Save(&str, i, '\0');
    CopyVec(&str, &new, str.size);

    return new.data;
}

vector_int* AlgBM(char* string, char* pattern) {
    char  date[255];
    char* start = pattern;
    char* end   = start + strlen(pattern) - 1;
    int   pattern_point = strlen(pattern) - 1;
    int   string_point  = strlen(pattern) - 1;
    int   tmp           = -1;
    int   tmp_point     = 0;
    vector_int* result = (vector_int *) malloc(sizeof(vector_int));
    CreateVec_int(result, 1);

    for (int i = 0; i < 255; i++)
        date[i] = strlen(pattern);

    while (*start != '\0') {
        if (end - start == 0)
            break;

        date[*start] = end - start;
        start++;
    }

    tmp = 0;
    tmp_point = string_point; 
    while (string_point < strlen(string)) {
        if (string[string_point] != pattern[pattern_point] && pattern_point == strlen(pattern) - 1) {
            string_point += date[string[string_point]];
            tmp_point = string_point;
        } else if (string[string_point] != pattern[pattern_point] && pattern_point != strlen(pattern) - 1 ) {
            string_point  = tmp_point + date[pattern[strlen(pattern) - 1]];
            pattern_point = strlen(pattern) - 1;
            tmp_point = string_point;
        } else if (string[string_point] == pattern[pattern_point]) {
            if (pattern_point == 0) {
                if (result->size <= tmp)
                    Resize_int(result, result->size * 2);
                Save_int(result, tmp, string_point);
                tmp++;
                string_point = tmp_point + strlen(pattern);
                pattern_point = strlen(pattern) - 1;
                continue;
            }
            pattern_point--;
            string_point--;
        }
    }

    if (tmp > 0)
        return result;
    else {
        Destroy_int(result);
        free(result);
        return NULL;
    }
}