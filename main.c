#include <stdio.h>
#include "wordlib.h"
#include <stdlib.h>
#include <string.h>

//TODO: test more conditionals, loops, comparators thru end
//TODO: test nested loops, nest conditionals in loops etc; extensive testing of nesting.

int main() {
    const char* program1 = "36 0 IF 36 0 IF EMIT ELSE . THEN EMIT ELSE 36 0 IF . ELSE EMIT THEN . THEN"; //works
    const char* program2 = "VARIABLE X 36 X ! X @ EMIT"; //works
    const char* program3 = "36 1 IF EMIT ELSE . THEN"; //works
    const char* program4 = "1 2 + 1 + 15 - 3 + -5 + . 10 33 100 108 114 111 87 32 44 111 108 108 101 72 10 EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT EMIT"; //works
    const char* program5 = "VARIABLE X 0 X ! X @ 4 < WHILE X @ 1 + X ! X @ . X @ 4 < 10 EMIT ENDWHILE"; //works
    const char* program6 = "36 -4 -4 <= IF EMIT ELSE . THEN"; //works with all conditionals and all combinations
    const char* program7 = "VARIABLE Y 0 Y ! VARIABLE X 0 X ! X @ 4 < WHILE 0 Y ! X @ 1 + X ! X @ . Y @ 2 < WHILE Y @ 1 + Y ! Y @ . Y @ 2 < ENDWHILE X @ 4 < ENDWHILE"; //works
    const char* program8 = "VARIABLE Y 36 Y ! VARIABLE X 37 X ! Y @ EMIT X @ EMIT"; //works
    const char* program9 = ": INCREMENTVAR DUP @ 1 + SWAP ! ; VARIABLE X 7 X ! X @ . 10 EMIT X INCREMENTVAR X @ ."; //works
    const char* program10 = ": CR 10 EMIT ; : SPACE 32 EMIT ; : FIRSTN DUP 0 OVER 0 > WHILE DUP . CR 1 + OVER OVER > ENDWHILE ; 5 FIRSTN";
    context_t* myContext = malloc(sizeof(context_t));
    init(program10, myContext);
    int j = 0;
    while(j != -1){
        j = execute(myContext);
        //printf("Execute is doing %.*s\n", myContext->currentLen, myContext->executionPoint);
        //printf("|%s|\n", myContext->executionPoint);
        //printf("Execute finished with status %d\n", j);
    }
    //printf("Execute finished with status %d\n", execute(myContext));
    //printf("Execute finished with status %d\n", execute(myContext));
    return 0;
}
