#include <stdio.h>
#include <stdlib.h>
#include "symbols.h"
#include <string.h>



SymbolTable scope = {NULL , 0 , NULL , NULL};



void insertToScope(Symbol *symbol){
    if(scope.symbols == NULL){
        scope.symbols = symbol;
        return;
    }

    Symbol *next = scope.symbols;
    while(1){
        if(next->next == NULL){
            next->next = symbol;
            next = next->next;
            return;
        }else{
            next = next->next;
        }
        
    }

    return ;
}


Symbol* searchInScope(char *name){
    Symbol *symbol = scope.symbols;
    if(symbol == NULL) return NULL;
    while(1){
        if(strcmp(symbol->name ,name) == 0){
            return symbol;
        }else{
            symbol = symbol->next;
            if(symbol == NULL){
                return NULL;
            }
        }

    }    
}


Symbol* createSymbol(SymbolTable *scope , char *name){
    Symbol* symbol = (Symbol * )malloc(sizeof(Symbol));
    symbol->name = name;
    symbol->next = NULL;

    insertToScope(symbol);
    return symbol;
}




