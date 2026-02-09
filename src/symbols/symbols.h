#ifndef SYMBOLS_H

typedef struct symbol{
    char * name;
    int value;
    struct symbol * next;
    struct symbol * endOfLink; 
} Symbol;


typedef struct symbolTable{
    struct symbolTable * parent;
    Symbol * symbols;
    struct symbolTable * childs;
    struct symbolTable * next;
}  SymbolTable;



Symbol* createSymbol(SymbolTable *scope , char *name);
Symbol* searchInScope(char *name);
void insertToScope(Symbol *symbol);



#define SYMBOLS_H
#endif