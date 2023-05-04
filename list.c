//
// Created by colin on 5/14/2021.
//
#include "list.h"
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include "util.h"

long int* addToVarList(varList_t* list, char* name, int len, int val) {
    long int* exists = find(list, name, len);
    if(exists == NULL) {
        var_t *new = malloc(sizeof(var_t));
        if (new == NULL) {
            printf("Runtime error: Unable to allocate memory");
            return NULL;
        } else if (list->size == 0) {
            new->next = NULL;
        } else {
            new->next = list->first;
        }
        new->val = val;
        exists = &(new->val);
        new->name = malloc(sizeof(char) * (len + 1));
        strncpy(new->name, name, len);
        (new->name)[len] = 0; //add null terminator
        list->first = new;
        list->size++;
        return exists; //needed?
    }
    else {
        //Do nothing if it already exists.
        //*exists = val;
    }
    return exists;
}

char* addToFuncList(funcList_t* list, char* name, int len, char* location) {
    func_t* exists = findFunc(list, name, len);
    if(exists == NULL) {
        exists = malloc(sizeof(func_t));
        if (exists == NULL) {
            printf("Runtime error: Unable to allocate memory");
            return NULL;
        } else if (list->size == 0) {
            exists->next = NULL;
        } else {
            exists->next = list->first;
        }
        //exists->location = location;
        int i = 0;
        while(location[i] != ';'){
            if(location[i] == 0){
                printf("Function definition is not terminated"); //TODO: crash
                return NULL;
            }
            i++;
        } i++;
        exists->location = malloc(i + 2);
        strncpy(exists->location, location, i);
        (exists->location)[i] = ' '; (exists->location)[i + 1] = 0; //TODO: test changes.
        exists->len = len;
        exists->name = malloc(sizeof(char) * (len + 1));
        strncpy(exists->name, name, len);
        (exists->name)[len] = 0; //add null terminator
        list->first = exists;
        list->size++;
    }
    else {
        printf("Illegal second declaration.\n"); //TODO: crash
        return NULL;
    }
    return exists->location;
}

long int* find(varList_t* list, char* name, int len) {
    var_t* iterator = list->first;
    while(iterator != NULL) {
        if(!strncmp(name, iterator->name, max(len, strlen(iterator->name)))) {
            return &(iterator->val);
        }
        iterator = iterator->next;
    }
    return NULL;
}

func_t* findFunc(funcList_t* list, char* name, int len) {
    //printf("Running\n");
    func_t* iterator = list->first;
    //printf("Running2\n");
    while(iterator != NULL) {
        if(!strncmp(name, iterator->name, max(len, strlen(iterator->name)))) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

void del(varList_t* list) {
    var_t* iterator = list->first;
    while(iterator != NULL) {
        free(iterator->name);
        free(iterator);
        iterator = iterator->next;
    }
}

void delFuncs(funcList_t* list) {
    func_t* iterator = list->first;
    while(iterator != NULL) {
        free(iterator->name);
        free(iterator);
        iterator = iterator->next;
    }
}

struct_t* findStruct(structList_t* list, char* name, int len){
    struct_t* iterator = list->first;
    while(iterator != NULL){
        if(!strncmp(name, iterator->type, max(len, strlen(iterator->type)))){
            return iterator;
        }
    }
    return NULL;
}

struct_t* addToStructList(structList_t* list, char* loc, int len){
    struct_t* s;
    if(findStruct(list, loc, len) == NULL){
        s = malloc(sizeof(struct_t));
        if (s == NULL){
            printf("Could not allocate memory for struct");
            return 0;
        }

        if (list->size == 0){
            list->first = s;
            s->next = NULL;
        }
        else {
            s->next = list->first;
            list->first = s;
        }
        s->type = malloc(sizeof(char) * (len + 1));
        strncpy(s->type, loc, len);
        s->variables = malloc(sizeof(varList_t));
        int i = 0;
        while(loc[i] != ';'){
            if(loc[i] == 0){
                printf("Struct definition is not terminated"); //TODO: crash
                return NULL;
            }
            i++;
        } i++;
        char* myLoc = loc;
        char* tmp = loc;
        while(*(myLoc) != ';'){
            addToVarList(s->variables, myLoc, dLen(myLoc), 0);
            tmp = myLoc + dLen(myLoc) + 1;
            long int val = 0;
            if(isValidNumber(tmp, dLen(tmp))){
                val = parseLongFromStr(tmp, dLen(tmp));
                addToVarList(s->variables, myLoc, dLen(myLoc), val); //TODO: resolve warning
                myLoc = tmp + dLen(tmp) + 1;
            }
            else {
                addToVarList(s->variables, myLoc, dLen(myLoc), 0);
                myLoc += dLen(myLoc) + 1;
            }
        }
    }
    else {
        return NULL;
    }
}

void copyVarList(varList_t* source, varList_t* dest){
    var_t* v = source->first;
    var_t* d = malloc(sizeof(var_t));
    d->next = NULL;
    while (v != NULL){
        d->val = v->val;
        d->name = v->name;
        d->next = (v->next == NULL) ? NULL : malloc(sizeof(var_t));
        v = v->next;
    }
}