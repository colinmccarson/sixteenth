#include "wordlib.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

const char* const keyWords[] = {".", "EMIT", "WORD", "VARIABLE", "!", "@", "IF", "ELSE", "THEN", "+",
                                "-", ">", ">=", "<", "<=", "==", "!=", "WHILE", "ENDWHILE", ";",
                                ":", "DUP", "SWAP", "OVER", "DEPTH"};
void (* const funptrs[])(context_t*) = {&print, &printAscii, &getInput, &createVar, &storeAt, &fetch, &conditional,
                                 &condElse, &then, &addition, &subtraction, &greaterThan, &greaterEqualThan, &lessThan, &lessEqualThan,
                                 &equals, &notEquals, &whileLoop, &endWhile, &endUserDefinedWord, &createUserDefinedWord, &duplicate, &swap, &over, &depth};
const int numKeyWords = 25;

void print(context_t *context) { //.
    long int x = popLong(context->stack);
    printf("%ld", x);
}

void printAscii(context_t *context) { //EMIT
    long int x = popLong(context->stack) % 0x100; //printable range
    char c = (char) x;
    char str[2] = {c, 0};
    //printf("%c", x);
    printf("%s", str);
}

void getInput(context_t *context) { //WORD
    long int x;
    scanf("%ld", &x); //Need to figure out how to handle conversion errors
    pushLong(x, context->stack);
}

void createVar(context_t *context) { //VARIABLE <type>. No scoping yet. Consumes 2 tokens.
    goNext(context); //Get the type
    char* name = context->executionPoint;
    addToVarList(context->globals, context->executionPoint, context->currentLen, 0); //For now variables are zero-initialized.
}

void varName(context_t *context) {
    long int *x = find(context->globals, context->executionPoint, context->currentLen);
    char* appendTo = "";
    if(x == NULL){
        printf("%s is not a word or a variable.", strncat(appendTo, (context->executionPoint), context->currentLen));
        //TODO: Stop execution
        return;
    }
    pushAddr(x, context->stack);
}

void freeMemory(context_t *context) {
    long int* loc = popAddr(context->stack);
    free(loc);
}

void storeAt(context_t *context) { // !
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }

    long int* loc = popAddr(context->stack);
    long int val = popLong(context->stack);
    *loc = val;
}

void fetch(context_t *context) { // @
    long int* addr = popAddr(context->stack);
    pushLong(*addr, context->stack);
}

void conditional(context_t *context) { // IF
    long int truthValue = popLong(context->stack);
    int thensToFind = 1; //Number of THEN's we need to find.
    char* blockReturn = NULL;
    char* elseReturn = NULL;
    char* lookAt = (context->executionPoint) + (context->currentLen) + 1;
    pushLong(0, context->conditionalStack); //The if which is the subject of this function call
    while(context->conditionalStack->size > 0) {
        if(strncmp(lookAt, "IF ", 3) == 0) {
            pushLong(0, context->conditionalStack);
        }
        else if(strncmp(lookAt, "ELSE ", 5) == 0) {
            if(context->conditionalStack->size == 1){
                elseReturn = lookAt;
            }
            pushLong(1, context->conditionalStack);
        }
        else if(strncmp(lookAt, "THEN ", 5) == 0) {
            long int isElse = popLong(context->conditionalStack); // BUG ?
            if(isElse){
                popLong(context->conditionalStack);
            }
            if(context->conditionalStack->size == 0){
                blockReturn = lookAt;
            }
        }
        lookAt = lookAhead(context, lookAt, 1);
    }
    if(truthValue){
        pushString(blockReturn, context->addressStack);
    }
    else {
        if(elseReturn == NULL){
            context->executionPoint = blockReturn;
            //context->currentLen = 4; //might remove
        }
        else {
            context->executionPoint = elseReturn;
            pushString(blockReturn, context->addressStack);
            //context->currentLen = 4; //might remove
        }
    }
}

void condElse(context_t *context) {//ELSE
    //This word is only executed when an IF condition is true - terminates the IF-part of the code.
    //context->executionPoint = popString(context->addressStack);
    context->executionPoint = (context->addressStack->top->data).word;
}

void then(context_t *context) { //THEN
    popString(context->addressStack);
}

void addition(context_t *context) {
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }
    long int arg2 = popLong(context->stack);
    long int arg1 = popLong(context->stack);
    pushLong(arg1 + arg2, context->stack);
}

void subtraction(context_t *context) { // -
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }
    long int arg2 = popLong(context->stack);
    long int arg1 = popLong(context->stack);
    //printf("Arg 1 is %ld, Arg 2 is %ld\n", arg1, arg2);
    pushLong(arg1 - arg2, context->stack);
}

void greaterThan(context_t *context) {
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }
    long int arg2 = popLong(context->stack);
    long int arg1 = popLong(context->stack);
    if(arg1 > arg2){
        pushLong(1, context->stack);
    }
    else pushLong(0, context->stack);
}

void greaterEqualThan(context_t *context) {
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }
    long int arg2 = popLong(context->stack);
    long int arg1 = popLong(context->stack);
    if(arg1 >= arg2) pushLong(1, context->stack);
    else pushLong(0, context->stack);
}

void lessThan(context_t *context) {
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }
    long int arg2 = popLong(context->stack);
    long int arg1 = popLong(context->stack);
    if(arg1 < arg2) pushLong(1, context->stack);
    else pushLong(0, context->stack);
}

void lessEqualThan(context_t *context) {
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }
    long int arg2 = popLong(context->stack);
    long int arg1 = popLong(context->stack);
    if(arg1 <= arg2) pushLong(1, context->stack);
    else pushLong(0, context->stack);
}

void equals(context_t *context) {
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }
    long int arg2 = popLong(context->stack);
    long int arg1 = popLong(context->stack);
    if(arg1 == arg2) pushLong(1, context->stack);
    else pushLong(0, context->stack);
}

void notEquals(context_t *context) {
    if(context->stack->size < 2){
        printf("Runtime Error: Stack underflow.");
        return;
    }
    long int arg2 = popLong(context->stack);
    long int arg1 = popLong(context->stack);
    if(arg1 != arg2) pushLong(1, context->stack);
    else pushLong(0, context->stack);
}

void whileLoop(context_t *context) { //WHILE
    long int truthValue = popLong(context->stack);
    int numWhiles = 1;
    char* lookAt = (context->executionPoint) + (context->currentLen) + 1;
    while(numWhiles > 0){
        if(strncmp(lookAt, "WHILE ", 6) == 0){
            numWhiles++;
        }
        else if (strncmp(lookAt, "ENDWHILE ", 9) == 0){
            numWhiles--;
        }
        lookAt = lookAhead(context, lookAt, 1);
    }
    char* endPoint = lookAt - 9;
    if(truthValue){
        pushString(context->executionPoint, context->addressStack); //push the beginning of loop body to the stack
    }
    else {
        context->executionPoint = endPoint;
    }
}

void endWhile(context_t *context) { //ENDWHILE
    //The user should always push the truth value right before ENDWHILE
    long int truthValue = popLong(context->stack);
    if(truthValue){
        context->executionPoint = (context->addressStack->top->data).word;
    }
    else {
        popString(context->addressStack);
    }
}

void duplicate(context_t* context){//DUP
    pushElement(context->stack->top, context->stack);
}

void swap(context_t* context){ //SWAP
    stackElement_t* temp = malloc(sizeof(stackElement_t));
    temp->data = context->stack->top->data;
    context->stack->top->data = context->stack->top->next->data;
    context->stack->top->next->data = temp->data;
    free(temp);
}

int isNumber(context_t *context) {
    char* word = context->executionPoint;
    if(context->currentLen == 0){
        //Cannot have numbers of length zero.
        return 0;
    }
    for(int i = 0; i < context->currentLen; i++){
        char c = *(word + i);
        if(c < 48 || c > 57){
            if(i == 0 && c == '-' && *(word + 1) != ' ') continue;
            else return 0;
        }
    }
    return 1;
}

int ipow(int base, int exp) {
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

long int parseLong(context_t *context) {
    long int num = 0;
    for(int i = 0; i < context->currentLen; i++){
        if(*(context->executionPoint) == '-'){
            if(i == 0) continue;
            num *= 10;
            num -= (*(context->executionPoint + i) - '0');
            //num -= (*(context->executionPoint + i) - '0') * ipow(10, context->currentLen - i - 2);
        }
        else {
            //num += (*(context->executionPoint + i) - '0') * ipow(10, context->currentLen - i - 1);
            num *= 10;
            num += *(context->executionPoint + i) - '0';
        }
    }
    return num;
}

int isKeyWord(context_t *context) {
    for(int i = 0; i < numKeyWords; i++){
        if(strncmp(context->executionPoint, keyWords[i], context->currentLen) == 0){
            return i;
        }
    }
    return -1;
}

int isUserDefinedWord(context_t *context) {
    if(findFunc(context->customWords, context->executionPoint, context->currentLen) != NULL){
        return 1;
    }
    else {
        return 0;
    }
}

int isVariable(context_t *context) {
    if(find(context->globals, context->executionPoint, context->currentLen) != NULL){
        return 1;
    }
    else {
        return 0;
    }
}

int execute(context_t *context) {
    //printf("Current len is %d\n", context->currentLen);
    //printf(context->executionPoint); printf("\n");
    if (*(context->executionPoint) == 0){
        printf(" ok\n");
        return -1;
    }
    else if((*(context->executionPoint) == ' ') || (*(context->executionPoint) == '\n')){ //TODO: necessary?
        /*if(*(context->executionPoint) == '\n'){
            printf("newline");
        }*/
        (context->executionPoint)++;
        return 8;
    }
    if(isNumber(context)){
        pushLong(parseLong(context), context->stack);
        goNext(context);
        //printf("Is Number!\n");
        return 7;
    }
    else{
        int j = isKeyWord(context);
        long int* var = find(context->globals, context->executionPoint, context->currentLen);
        //printf("The value of j is %d\n", j);
        func_t* k = findFunc(context->customWords, context->executionPoint, context->currentLen);
        //printf("The value of k is %p\n", k);
        if(j != -1){
            funptrs[j](context);
            goNext(context);
            //printf("Keyword!\n");
            //printf("%s", context->executionPoint); printf("\n");
            return 0;
        }
        else if (var != NULL){
            pushAddr(var, context->stack);
            goNext(context);
            return 2;
        }
        else if ( k != NULL){
            pushString(context->executionPoint, context->addressStack);
            context->executionPoint = k->location;
            context->currentLen = getCurrentLen(context->executionPoint);
            return 1;
        }
        else {
            printf("Unrecognized word at:%s\n", context->executionPoint);
            return -1;
        }
    }
}

void createUserDefinedWord(context_t *context) { // :
    goNext(context);
    int i = isNumber(context);
    int j = isVariable(context);
    int k = isKeyWord(context) != -1;
    int l = isUserDefinedWord(context);
    if(i || k || j || l){
        printf("Illegal user-defined word type.\n");
        return;
    }
    else {
        addToFuncList(context->customWords, context->executionPoint, context->currentLen,
                      context->executionPoint + context->currentLen + 1);
    }
    while(strncmp(context->executionPoint, "; ", 2) != 0){
        goNext(context);
    }
}

void endUserDefinedWord(context_t *context) { // ;
    context->executionPoint = popString(context->addressStack);
    context->currentLen = getCurrentLen((context->executionPoint));
}

void over(context_t *context) { //OVER
    pushElement(context->stack->top->next, context->stack);
}

void depth(context_t* context){ //DEPTH
    pushLong(context->stack->size, context->stack);
}

void defineStruct(context_t* context){ // STRUCT
    goNext(context);
    struct_t* s;
    int i = isNumber(context);
    int j = isVariable(context);
    int k = isKeyWord(context) != -1;
    int l = isUserDefinedWord(context);
    if(i || j || k || l){
        printf("Illegal struct type.");
        return; //TODO: consume tokens until struct is terminated
    }
    else {
        s = addToStructList(context->customStructs, context->executionPoint, context->currentLen);
    }
    while(strncmp(context->executionPoint, "; ", 2) != 0){
        goNext(context);
    }
}

void instantiateStruct(context_t* context){ //MKSTRUCT

}

int isStruct(context_t* context){
    struct_t* s = findStruct(context->customStructs, context->executionPoint, context->currentLen);
}