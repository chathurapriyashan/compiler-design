#include <stdio.h>
#include <stdlib.h>
#include "symbols.h"

struct symbol{
    char * name;
    char * value;
    struct symbol * next;
    struct symbol * endOfLink; 
} ;


struct symbolTable{
    struct symbolTable * parent;
    Symbol * symbols;
    struct symbolTable * childs;
    struct symbolTable * next;
} ;



SymbolTable *createScope(SymbolTable *parentScope){
    SymbolTable* scope = (SymbolTable *) malloc(sizeof(SymbolTable));
    scope->parent = parentScope;
    scope->symbols = NULL;
    return scope;
}


void deleteSymbol(Symbol * symbol){
    free(symbol);
}

void deleteScope(SymbolTable *st){
    if(st->symbols == NULL){
        free(st);
        return;
    }

    Symbol * symbol = st->symbols;
    while (1){
        Symbol * next = symbol->next;
        free(symbol);
        if(next == NULL) return;
    }

    free(st);
    return;
    
}



void insertToScope(SymbolTable * scope , Symbol * symbol){
    
    if(scope->symbols == NULL){
        scope->symbols = symbol;
        return;
    }

    Symbol* next = scope->symbols;

    while (1){
        if(next->next == NULL){
            next->next = symbol;
            return;
        }

        next = next->next;
    }
    
}


SymbolTable* createSymbol(SymbolTable *scope , char *name , char *value){
    Symbol* symbol = (Symbol * )malloc(sizeof(Symbol));
    symbol->name = name;
    symbol->value = value;
    symbol->next = NULL;

    insertToScope(scope , symbol);
    return scope;
}




