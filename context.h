//
// Created by colin on 5/15/2021.
//

#ifndef FORTHINTERPRETER_CONTEXT_H
#define FORTHINTERPRETER_CONTEXT_H
#include "stack.h"
#include "list.h"

typedef struct {
    char* executionPoint;
    char* programBegin;
    int currentLen;
    stack_t* stack;
    stack_t* conditionalStack; //Not for public use. Used by IF keyword only.
    stack_t* addressStack;
    varList_t* globals;
    funcList_t* customWords;
    structList_t* customStructs;
    structObjList_t* instantiatedStructs;
} context_t;

void init(char* program, context_t* context);
void goNext(context_t* context);
char* lookAhead(context_t* context, char* begin, int numWords);
int getCurrentLen(char* string);
void safeCopy(char* source, char* dest, int len);
int execute(context_t* context);
void contextDestructor(context_t* context);
void clearContext(context_t* context);
void setProgram(char* program, context_t* context);
void clearProgram(context_t* context);

#endif //FORTHINTERPRETER_CONTEXT_H
