//
// Created by colin on 9/14/2021.
//

#ifndef FORTHINTERPRETER_WORDLIB_H
#define FORTHINTERPRETER_WORDLIB_H

//
// Created by colin on 4/19/2021.
//
#include "context.h"

void print(context_t* context);

void printAscii(context_t* context);

void getInput(context_t* context);

void createVar(context_t* context);

void varName(context_t* context);

void freeMemory(context_t* context);

void storeAt(context_t* context);

void fetch(context_t* context);

void conditional(context_t* context);

void condElse(context_t* context);

void then(context_t* context);

void addition(context_t* context);

void subtraction(context_t* context);

//Comparators

void greaterThan(context_t* context);

void greaterEqualThan(context_t* context);

void lessThan(context_t* context);

void lessEqualThan(context_t* context);

void equals(context_t* context);

void notEquals(context_t* context);

void whileLoop(context_t* context);

void endWhile(context_t* context);

int isNumber(context_t* context);

int ipow(int base, int exp);

long int parseLong(context_t* context);

extern const char* const keyWords[];
extern void (* const funptrs[])(context_t*);
extern const int numKeyWords;

int isKeyWord(context_t* context);

int isUserDefinedWord(context_t* context);

int isVariable(context_t* context);

int execute(context_t* context);

void createUserDefinedWord(context_t* context);

void endUserDefinedWord(context_t* context);

void duplicate(context_t* context);

void swap(context_t* context);

void over(context_t *context);

#endif //FORTHINTERPRETER_WORDLIB_H
