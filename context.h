//
// Created by colin on 5/15/2021.
//

#ifndef FORTHINTERPRETER_CONTEXT_H
#define FORTHINTERPRETER_CONTEXT_H
#include "stack.h"
#include "list.h"

typedef struct {
    char* executionPoint;
    int currentLen;
    stack_t* stack;
    stack_t* conditionalStack; //Not for public use. Used by IF keyword only.
    stack_t* addressStack;
    varList_t* globals;
    funcList_t* customWords;
} context_t;

void init(const char* program, context_t* context);
void goNext(context_t* context);
char* lookAhead(context_t* context, char* begin, int numWords);
int getCurrentLen(char* string);
void safeCopy(char* source, char* dest, int len);
int execute(context_t* context);

#endif //FORTHINTERPRETER_CONTEXT_H
