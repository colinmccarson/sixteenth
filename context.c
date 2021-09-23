//
// Created by colin on 5/15/2021.
//

#include "context.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void goNext(context_t* context) {
    context->currentLen = getCurrentLen(context->executionPoint);
    context->executionPoint += (context->currentLen) + 1;
    if(*(context->executionPoint) == 0){
        context->currentLen = 0;
        //printf("End of program\n");
        return;
    }
    context->currentLen = getCurrentLen((context->executionPoint));
}

char* lookAhead(context_t* context, char* begin, int numWords) {
    for(int i = 0; i < numWords; i++) {
        while ((*begin) != ' ' && (*begin) != 0) {
            begin++;
        }
        if ((*begin) == 0) {
            //printf("lookAhead reached end of program.\n");
            return begin;
        }
        begin++; //Begin now points to the beginning of the next word.
    }
    return begin;
}

int getLenNext(context_t* context) {
    char* copy = context->executionPoint + context->currentLen + 1;
    int i = 0;
    //Get the length of the next word, without null terminator
    while((*copy) != ' ') {
        copy += 1;
        i++;
    }
    return i + 1;
}

int getCurrentLen(char* string) {
    int i = 0;
    while(*(string + i) != ' ' && *(string) != 0) {
        i++;
    }
    return i; //Number of characters till the whitespace, inclusive.
}

void safeCopy(char* source, char* dest, int len) {
    for(int i = 0; i < len; i++) {
        *(source + i) = *(dest + i);
    }
}

void init(char* program, context_t* context){
    //context->executionPoint = program;
    context->currentLen = getCurrentLen(program);

    context->addressStack = malloc(sizeof(stack_t));
    context->conditionalStack = malloc(sizeof(stack_t));
    context->stack = malloc(sizeof(stack_t));
    context->stack->size = 0;
    context->stack->top = NULL;
    context->addressStack->size = 0;
    context->addressStack->top = NULL;
    context->conditionalStack->size = 0;
    context->conditionalStack->top = NULL;

    context->globals = malloc(sizeof(varList_t));
    context->globals->first = NULL;
    context->globals->size = 0;
    context->customWords = malloc(sizeof(funcList_t));
    context->customWords->first = NULL;
    context->customWords->size = 0;
    setProgram(program, context);
}

void contextDestructor(context_t* context){
    clearContext(context);
}

void setProgram(char* program, context_t* context){
    char* lookAt = program;

    while((*lookAt) != 0){
        lookAt = lookAhead(context, lookAt, 1);
    }
    if(*(lookAt - 1) != ' '){
        //printf("Adding whitespace.\n");
        unsigned long size = strlen(program) + 2; // + whitespace + nullterm
        context->programBegin = malloc(size);
        strncpy(context->programBegin, program, size);
        (context->programBegin)[size-2] = ' '; (context->programBegin)[size-1] = 0;
    }
    else {
        context->programBegin = malloc(strlen(program));
        strncpy(context->programBegin, program, strlen(program));
    }
    context->executionPoint = context->programBegin;
}

void clearProgram(context_t* context){
    free(context->programBegin);
}

void clearContext(context_t* context){
    free(context->programBegin); //Need to reset to beginning of program.
    while(context->conditionalStack->size > 0){
        popLong(context->conditionalStack);
    }
    while(context->addressStack->size > 0){
        popString(context->addressStack);
    }
    while(context->stack->size > 0){
        popLong(context->stack);
    }
    del(context->globals);
    delFuncs(context->customWords);
}