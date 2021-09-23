//
// Created by colin on 9/17/2021.
//
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getLine(shell_t* shell){
    char input[512];
    //scanf("%s", input);
    fgets(input, 512, stdin);
    for(int i = 0; i < 512; i++){
        if(input[i] == '\n'){
            input[i] = ' ';
        }
    }
    shell->currentLine = malloc(strlen(input));
    for(int i = 0; i < strlen(shell->currentLine); i++){
        if (*(shell->currentLine + i) == '\n'){
            (shell->currentLine)[i] = ' ';
        }
    }
    strncpy(shell->currentLine, input, strlen(input));
    if(!(shell->contextInitialized)){
        init(shell->currentLine, shell->context);
        shell->contextInitialized = 1;
    }
    else {
        setProgram(shell->currentLine, shell->context);
        //TODO: THIS DOES NOT WORK. Need to 'build' program as we go, because user-defined functions reference strings.
        //TODO: either build as we go or change implementation of user-defined functions to copy string. Latter seems preferable.
    }
}

int shellExecute(shell_t* shell){
    int j = 0;
    if(strncmp(shell->currentLine, "STOP", 4) == 0){
        return -1;
    }
    while(j != -1){
        j = execute(shell->context);
    }
    return 0;
}

void clearState(shell_t* shell){
    free(shell->currentLine);
    clearProgram(shell->context);
}

void initShell(shell_t* shell){
    shell->context = malloc(sizeof(context_t));
    shell->contextInitialized = 0;
    //init("", shell->context);
}