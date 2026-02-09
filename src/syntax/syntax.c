#include <stdio.h>
#include <stdlib.h>
#include "../lexer/lexer.h"
#include "syntax.h"
#include "../symbols/symbols.h"
#include <string.h>
#include <stdlib.h>



/*
----------------------
----------------------
Program → StatementList

StatementList → Statement StatementList | ε
              

Statement → VarDecl ';'
           | Assignment ';'
           | PrintStmt ';'
           | Expr ;

VarDecl → 'int' id '=' Expr           // Variable declaration with initialization

Assignment → id '=' Expr              // Assign expression to existing variable

PrintStmt → 'print' '(' IdList ')'

IdList → id IdListTail
       | num IdListTail

IdListTail → ',' id IdListTail
           | ',' num IdListTail
           | ε

Expr → Term | Term ExprTail

ExprTail → '+' Term ExprTail
          | '-' Term ExprTail
          | ε

Term → Factor TermTail

TermTail → '*' Factor TermTail
          | '/' Factor TermTail
          | '%' Factor TermTail
          | ε

Factor → '(' Expr ')'
        | id
        | num

*/


Token *lookahead;

/* ---------- Error handling ---------- */
void syntaxError(const char *msg) {
    printf("Syntax Error: %s\n", msg);
    if (lookahead)
        printf("At token type %d, value '%s'\n", lookahead->type, lookahead->value);
    exit(1);
}

/* ---------- Match function ---------- */
Token* match(Type expected) {
    Token *t = lookahead;
    if (lookahead && lookahead->type == expected) {
        lookahead = nextToken();  // consume
        return t;
    } else {
        syntaxError("Unexpected token");
    }

    return NULL;
}


void Program() {
    StatementList();
}


void StatementList() {
    if (lookahead == NULL) return;

    switch (lookahead->type) {
        case INT:
        case ID:
        case PRINT:
        case N_BRACKETS_OPEN:
        case NUM_INT:
        case NUM_FLOAT:
            Statement();
            StatementList();
            break;
        default:
            return; // ε
    }
}


void Statement() {
    if (lookahead->type == INT) {
        VarDecl();
        match(SEMICOLON);
    }
    else if (lookahead->type == ID) {
        Assignment();
        match(SEMICOLON);
    }
    else if (lookahead->type == PRINT) {
        PrintStmt();
        match(SEMICOLON);
    }
    else {
        int value = Expr();
        match(SEMICOLON);
    }
}


void VarDecl() {
    match(INT);
    Token *id = match(ID);
    Symbol *idSymbol = createSymbol(NULL , id->value);
    match(ASSIGN);
    idSymbol->value = Expr();
}


void Assignment() {
    Token *id = match(ID);
    Symbol* idSymbol = searchInScope(id->value);
    if(idSymbol == NULL){
        printf("Assignment to non declared variable called : %s\n" , id->value); 
        return;
    }

    match(ASSIGN);
    idSymbol->value = Expr();
}


void PrintStmt() {
    match(PRINT);
    match(N_BRACKETS_OPEN);
    IdList();
    match(N_BRACKETS_CLOSE);
}


void IdList() {
    if (lookahead->type == ID) {
        Token *id = match(ID);
        Symbol *idSymbol = searchInScope(id->value);
        if(idSymbol == NULL){
            printf("undefined variable called : %s\n" , id->value);
            return;
        }
        printf("%d " , idSymbol->value);
        IdListTail();
    }
    else if (lookahead->type == NUM_INT || lookahead->type == NUM_FLOAT) {
        match(lookahead->type);
        IdListTail();
    }
    else {
        syntaxError("Expected identifier or number in IdList");
    }
}


void IdListTail() {
    if (lookahead->type == COMMA) {
        match(COMMA);

        if (lookahead->type == ID) {
            Token* id = match(ID);
            Symbol *idSymbol = searchInScope(id->value);
            if(idSymbol == NULL){
                printf("undefined variable called : %s\n" , id->value);
                return;
            }
            printf("%d " , idSymbol->value);
        }
        else if (lookahead->type == NUM_INT || lookahead->type == NUM_FLOAT) {
            match(lookahead->type);
        }
        else {
            syntaxError("Expected id or number after comma");
        }

        IdListTail();
    }
}


int Expr() {
    int t = Term();
    int e = ExprTail();
    return t + e;
}


int ExprTail() {
    if (lookahead->type == PLUS) {
        match(PLUS);
        int t = Term();
        int e = ExprTail();
        return t + e;
    }
    else if (lookahead->type == HYPHEN) {
        match(HYPHEN);
        int t = Term();
        int e = ExprTail();
        return -1 * t + e;
    }
    return 0;
}


int Term() {
    int f = Factor();
    int t = TermTail();
    return f + t;
}


int TermTail() {
    if (lookahead->type == MUL) {
        match(MUL);
        int f = Factor();
        int t = TermTail();
    }
    else if (lookahead->type == DIVIDE) {
        match(DIVIDE);
        int f = Factor();
        int t = TermTail();
        return f + t;
    }
    else if (lookahead->type == MOD) {
        match(MOD);
        int f = Factor();
        int t = TermTail();
        return f + t;
    }
    return 0;

}



int Factor() {
    if (lookahead->type == N_BRACKETS_OPEN) {
        match(N_BRACKETS_OPEN);
        int e = Expr();
        match(N_BRACKETS_CLOSE);
        return e;
    }
    else if (lookahead->type == ID) {
        Token *t = match(ID);
        Symbol *s = searchInScope(t->value);
        if(s == NULL){
            printf("Undefined Variable called : %s\n" , t->value);
            syntaxError("Undefined Variable \n");
        }
        return s->value;
    }
    else if (lookahead->type == NUM_INT || lookahead->type == NUM_FLOAT) {
        Token *t = match(lookahead->type);
        return atoi(t->value);
        
    }
    else {
        syntaxError("Invalid factor");
    }

    return 0;
}


int syntaxAnalyzer() {
    lookahead = nextToken();  

    Program();

    if (lookahead != NULL) {
        syntaxError("Extra tokens after program end");
    }

    return 1;
}

