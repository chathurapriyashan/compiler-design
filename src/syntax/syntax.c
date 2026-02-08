#include "syntax.h"
#include "../lexer/lexer.h"
#include <stdio.h>
#include <string.h>



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


char logs[1024]; 




void error(Token *t , char * str){
    strcpy(logs , str);
    printf("%s" , logs);
}

Token *err_token = NULL;
void setErrorToken(Token *t){
    err_token = t;
}

Token *getErrorToken(){
    return err_token;
}

// Program → StatementList
bool Program(){
    bool stl = StatementList();
    return stl;
}

// StatementList → Statement StatementList
bool StatementList(){
    if(islastToken()) return true;

    bool st = Statement();
    if(!st) return false;


    return StatementList();

}
/*
Statement → VarDecl ';'
           | Assignment ';'
           | PrintStmt ';'
           | Expr ;
*/
int i = 0;
bool Statement(){
    tokenSave();
    bool v = VarDecl();
    
    if(v) {
        return true;
    }else{
        setErrorToken(nextToken());
        tokenRollback();

    }
    
    bool a = Assignment();
    if(a) {
        printf("%d next %p\n" ,a , nextToken());
        return true;
    }else{
        setErrorToken(nextToken());
        tokenRollback();

    }
    


    bool p = PrintStmt();
    if(p){
        return true;
    }else{
        setErrorToken(nextToken());
        tokenRollback();
    }

    bool e = Expr();
    if(e){
        return true;
    }else{
        setErrorToken(nextToken());
        tokenRollback();
    }


    bool n = isNull();
    if(n){
        return true;
    }else{
        setErrorToken(nextToken());
        tokenRollback();
    }


    return false;
    

}
// Assignment → id '=' Expr ';'
bool Assignment(){
    Token *t = nextToken();
    if(t == NULL) return false;
    if(t->type == SEMICOLON) return true;
    
    if(t->type == ID){
        t = nextToken();        
        if(t == NULL) return false;
        if(t->type == ASSIGN){
            bool e =  Expr();
            if(!e) return false;
            t = nextToken();
            if(t == NULL) return false;
            if(t->type == SEMICOLON) {
                return true;
            }
            else return false;
            
        }else{
            return false;
        }
    }else{
        return false;
    }

    return true;

}

bool isNull(){
    Token *t = nextToken();
    if(t == NULL) return true;
    else return false;
}

bool VarDecl(){
    Token *t = nextToken();
    if(t == NULL) return false;
    if(t->type == SEMICOLON) return true;


    if(t->type == INT || t->type == FLOAT || t->type == DOUBLE || t->type == SHORT){
        t = nextToken();
        if(t->type == ID){
            t = nextToken();
            if(t == NULL) return false;
            if(t->type == ASSIGN){
                bool e = Expr();
                if(!e) return false;
                t = nextToken();
                if(t == NULL) return false;
                if(t->type == SEMICOLON){
                    return true;
                }else{
                    return false;
                }
            }else if(t->type == SEMICOLON){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }

    }else{
        return false;
    }

    return false;

}

// PrintStmt → 'print' '(' IdList ')'
bool PrintStmt(){
    Token *t = nextToken();
    if(t == NULL) return false;

    if(t->type == PRINT){
        t = nextToken();
        if(t == NULL) return false;
        if(t->type != N_BRACKETS_OPEN)  return false;
        bool idl = IdList();
        if(!idl) return false;

        t = nextToken();
        if(t == NULL) return false;
        if(t->type != N_BRACKETS_CLOSE)  return false;
        
        t = nextToken();
        if(t == NULL) return false;
        if(t->type != SEMICOLON)  return false;
        else return true;
    }else{
        return false;
    }
    return false;
}

/*
IdList → id IdListTail
        | num IdListTail    
*/
bool IdList(){
    Token* t = nextToken();
    if(t == NULL) return false;
    if(t->type == ID || t->type == NUM_INT || t->type == NUM_FLOAT){
        return IdListTail();
    }else{
        return false;
    }

    return true;

}
/*
IdListTail → ',' id IdListTail
    | ',' num IdListTail
    | ε
*/
bool IdListTail(){
    Token *t = nextToken();

    if(t->type == COMMA){
        bool idl = IdList();
        return idl;
    }else{
        previousToken();
    }   
    return true;
}

// Expr → Term ExprTail
bool Expr(){
    bool t = Term();
    bool et = ExprTail();
    return t && et;
}

/*
ExprTail → '+' Term ExprTail
          | '-' Term ExprTail
          | ε
*/
bool ExprTail(){
    Token* t = nextToken();
    if(t == NULL) return false;
    if(t->type == PLUS || t->type == HYPHEN){
        bool t = Term();
        return t && ExprTail();

    }else{
        previousToken();
    }

    return true;
}

// Term → Factor TermTail
bool Term(){
    bool f = Factor();
    bool tt = TermTail();
    return f && tt;

}

bool TermTail(){
    return true;

}

/*
Factor → '(' Expr ')'
        | id
        | num

*/
bool Factor(){
    Token *t = nextToken();
    if(t == NULL) return false;
    if(t->type == ID || t->type == NUM_INT || t->type == NUM_FLOAT) return true;

    if(t->type == N_BRACKETS_OPEN){
        bool e = Expr();
        if(!e) return false;
        t = nextToken();
        if(t == NULL) return false;
        if(t->type == N_BRACKETS_CLOSE) return true;
        return true;
    }
    return false;
}


int syntaxAnalyzer(){
    bool status = Program();
    if(status == false){
        printTokenStream(getErrorToken());
        printf(" <<<<<<<< ERROR :: UNEXPECTED TOKEN\n");
        
    }

    return status;
}