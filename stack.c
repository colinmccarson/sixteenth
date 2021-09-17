//
// Created by colin on 5/13/2021.
//
#include <stddef.h>
#include <stdlib.h>
#include "stack.h"

void pushLong(long int data, stack_t* stack){
    stackElement_t* element = malloc(sizeof(stackElement_t));
    (element->data).val = data;
    element->next = stack->top;
    stack->top = element;
    (stack->size)++;
}

void pushAddr(long int* data, stack_t* stack) {
    stackElement_t* element = malloc(sizeof(stackElement_t));
    (element->data).ptr = data;
    element->next = stack->top;
    stack->top = element;
    (stack->size)++;
}

long int popLong(stack_t* stack){
    long int data = (stack->top->data).val;
    stackElement_t* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    (stack->size)--;
    return data;
}

long int* popAddr(stack_t* stack) {
    long int* data = (stack->top->data).ptr;
    stackElement_t* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    (stack->size)--;
    return data;
}

void pushString(char* data, stack_t* stack){
    stackElement_t* element = malloc(sizeof(stackElement_t));
    element->next = stack->top;
    stack->top = element;
    (element->data).word = data;
    (stack->size)++;
}

char* popString(stack_t* stack){
    char* data = (stack->top->data).word;
    stackElement_t* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    (stack->size)--;
    return data;
}

void pushElement(stackElement_t* element, stack_t* stack){
    stackElement_t* new = malloc(sizeof(stackElement_t));
    new->next = stack->top;
    new->data = element->data;
    stack->top = new;
    (stack->size)++;
}