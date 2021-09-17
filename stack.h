//
// Created by colin on 5/13/2021.
//

#ifndef FORTHINTERPRETER_STACK_H
#define FORTHINTERPRETER_STACK_H
#include<stddef.h>

typedef struct stackElement_s stackElement_t;

typedef struct {
    stackElement_t* top;
    size_t size;
} stack_t;

struct stackElement_s {
    struct stackElement_s* next;
    union data_t {
        long int val;
        long int* ptr;
        char* word;
    } data;
};


void pushLong(long int data, stack_t* stack);
void pushAddr(long int* data, stack_t* stack);
long int* popAddr(stack_t* stack);
long int popLong(stack_t* stack);
void pushString(char* data, stack_t* stack);
char* popString(stack_t* stack);
void pushElement(stackElement_t* element, stack_t* stack);



#endif //FORTHINTERPRETER_STACK_H
