#include "webHelper.h"
#include "stack.h"
#include "context.h"
#include <stdlib.h>
#include "list.h"
#include <string.h>

void setContext(char* info, context_t* context) {
    size_t mode = 3; //0=DATA, 1=VARS, 2=USERDEFINED, 3=PROGRAM
    size_t start = 0;
    size_t end = 0;
    size_t length = strlen(info);
    for (size_t i = 0; i < length; i++) {
        char* debug = info + i;
        if (info[i] == 10) {
            char* copy;
            size_t copyLength = i - start; //no +1 because we want to exclude the \n character
            copy = malloc(copyLength + 1); // +1 for null terminator
            for (int j = 0; j < copyLength; j++) { //strncpy
                copy[j] = info[start + j];
            }
            copy[copyLength] = 0; // no +1 because of 0-indexing

            if (!strncmp(copy, "__DATA__", 9)) {
                mode = 0;
            }
            else if (!strncmp(copy, "__VARS__", 9)) {
                mode = 1;
            }
            else if (!strncmp(copy, "__USERDEFINED__", 16)) {
                mode = 2;
            }
            else if (!strncmp(copy, "__PROGRAM__", 12)) {
                mode = 3;
            }
            else {
                if (mode == 0) { //check for mode
                    long int toAdd = atol(copy);
                    pushLong(toAdd, context->stack);
                }
                else if (mode == 1) {
                    char* varName;
                    size_t varNameLength = 0;
                    while (copy[1 + varNameLength] != ',') {
                        varNameLength++;
                    }
                    varName = malloc(varNameLength + 1);
                    for (int j = 0; j < varNameLength; j++) { //strncpy
                        varName[j] = copy[j + 1];
                    }
                    varName[varNameLength] = 0;
                    char* varValue;
                    varValue = malloc(copyLength - varNameLength - 3 + 1);
                    for (int j = 0; j < copyLength - varNameLength - 3; j++) {
                        varValue[j] = copy[varNameLength + j + 2];
                    }
                    varValue[copyLength - varNameLength - 3] = 0;
                    long int toAdd = atol(varValue);
                    addToVarList(context->globals, varName, varNameLength, toAdd);
                }
                else if (mode == 2) {
                    size_t spaceCount = 0;
                    char* funcName = copy + 2;
                    size_t funcNameLength = 0;
                    char* location;
                    while (copy[funcNameLength + 2] != ' ') {
                        funcNameLength++;
                    }
                    location = copy + funcNameLength + 2 + 1;
                    addToFuncList(context->customWords, funcName, funcNameLength, location);
                }
                else if (mode == 3) {
                    init(copy, context);
                }
            }
            start = i + 1;
            free(copy);
        }
    }
}