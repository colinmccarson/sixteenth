//
// Created by colin on 9/8/2021.
//

#ifndef FORTHINTERPRETER_UTIL_H
#define FORTHINTERPRETER_UTIL_H
int max(int x, int y){
    if(x > y) return x;
    else return y;
}

int min(int x, int y){
    if(x < y) return x;
    else return y;
}

int dLen(char* str){ //whitespace or null char delimited length
    int absLen = strlen(str);
    int i = 0;
    while(i < absLen && *(str + i) != ' '){
        i++;
    }
    return i;
}
//TODO: rewrite the corresponding functions in wordlib.c or remove entirely and refactor
int isValidNumber(char* str, int len) {
    char* word = str;
    if(len == 0){
        //Cannot have numbers of length zero.
        return 0;
    }
    for(int i = 0; i < len; i++){
        char c = *(word + i);
        if(c < 48 || c > 57){
            if(i == 0 && c == '-' && *(word + 1) != ' ') continue;
            else return 0;
        }
    }
    return 1;
}

long int parseLongFromStr(char* str, int len) {
    long int num = 0;
    for(int i = 0; i < len; i++){
        if(*(str) == '-'){
            if(i == 0) continue;
            num *= 10;
            num -= (*(str + i) - '0');
            //num -= (*(context->executionPoint + i) - '0') * ipow(10, context->currentLen - i - 2);
        }
        else {
            //num += (*(context->executionPoint + i) - '0') * ipow(10, context->currentLen - i - 1);
            num *= 10;
            num += *(str + i) - '0';
        }
    }
    return num;
}
#endif //FORTHINTERPRETER_UTIL_H
