//
// Created by colin on 5/14/2021.
//

#ifndef FORTHINTERPRETER_LIST_H
#define FORTHINTERPRETER_LIST_H
#include<stddef.h>

struct var_s {
    char* name;
    long int val;
    struct var_s* next;
};

typedef struct var_s var_t;

typedef struct {
    var_t* first;
    size_t size;
} varList_t;

struct func_s {
    char* name;
    int len;
    char* location;
    struct func_s* next;
};

typedef struct func_s func_t;

typedef struct {
    func_t* first;
    size_t* size;
} funcList_t;

struct struct_s {
    char* type;
    varList_t* variables; //TODO: refactor; change from being a varlist to being DA array of names
    struct struct_s* next;
};

typedef struct struct_s struct_t;

typedef struct {
    struct_t* first;
    size_t* size;
} structList_t;

struct structObj_s {
    char* name;
    struct_t* _s;
    struct structObj_s* next;
};

typedef struct structObj_s structObj_t;

typedef struct {
    structObj_t* first;
    size_t* size;
} structObjList_t;

long int* addToVarList(varList_t* list, char* name, int len, int val);

char* addToFuncList(funcList_t* list, char* name, int len, char* location);

long int* find(varList_t* list, char* name, int len);

func_t* findFunc(funcList_t* list, char* name, int len);

void del(varList_t* list);

void delFuncs(funcList_t* list);

struct_t* findStruct(structList_t*, char* name, int len);

struct_t* addToStructList(structList_t* list, char* loc, int len);

void copyVarList(varList_t* source, varList_t* dest);

#endif //FORTHINTERPRETER_LIST_H
