//
// Created by colin on 9/17/2021.
//
#include "context.h"
#ifndef FORTHINTERPRETER_SHELL_H
#define FORTHINTERPRETER_SHELL_H

typedef struct {
    context_t* context;
    char* currentLine;
    int contextInitialized;
} shell_t;

void getLine(shell_t* shell);

int shellExecute(shell_t* shell);

void initShell(shell_t* shell);

void clearState(shell_t* shell);

#endif //FORTHINTERPRETER_SHELL_H
