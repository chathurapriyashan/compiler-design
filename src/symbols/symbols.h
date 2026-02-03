#ifndef SYMBOLS_H

typedef struct symbol Symbol;
typedef struct symbolTable SymbolTable;


SymbolTable *createScope(SymbolTable *parentScope);
void deleteSymbol(Symbol * symbol);
void deleteSymbol(Symbol * symbol);
void deleteScope(SymbolTable *st);
void insertToScope(SymbolTable * scope , Symbol * symbol);
SymbolTable* createSymbol(SymbolTable *scope , char *name , char *value);













#define SYMBOLS_H
#endif