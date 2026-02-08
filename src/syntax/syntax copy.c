#include "syntax.h"
#include "../lexer/lexer.h"
#include <stdio.h>
#include <string.h>


/*
----------------------
E   → Expression
T   → Term
F   → Factor

---------------------

Program        → StatementList

StatementList  → Statement  StatementList | ε

Statement      →  V ;
        | PrintStmt ';'

V        → int id = E | E 

PrintStmt → print ( IdList )

IdList         → id IdListTail
                | num IdListTail
IdListTail     → , id  
                | , num
                | IdListTail 
                | ε

E  → T E'
E' → + T E'
    | - T E'
    | ε

T  → F T'
T' → * F T'
    | / F T'
    | % F T'
    | ε

F  → ( E )
    | id
    | num
*/

/*
----------------------
Program → StatementList

StatementList → Statement StatementList
              | ε

Statement → VarDecl ';'
           | PrintStmt ';'

VarDecl → 'int' id '=' Expr
        | id '=' Expr          // assignment without declaration

PrintStmt → 'print' '(' IdList ')'

IdList → id IdListTail
        | num IdListTail

IdListTail → ',' id IdListTail
           | ',' num IdListTail
           | ε

Expr → Term ExprTail

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

void error(char * str){
    strcpy(logs , str);
    printf("%s" , logs);
}

bool Program(){
    bool slt = StatementList();
    if(slt == false){
        error("statement list error | PROGRAM\n");

    }
    return slt;
}

bool StatementList(){
    bool st = Statement();
    bool stl = StatementList();
    return st && stl;

}

bool Statement(){
    bool v= V();
    if(v == true){ 
        Token *t =  nextToken();
        if(t->type == SEMICOLON ){
            return true;
        }
    }

    bool p = Print();

    if(p == true){
        Token *t =  nextToken();
        if(t->type == SEMICOLON ){
            return true;
        }
    }

    return false;
}


bool V(){
    Token *t = nextToken();
    if(t == NULL) return false;
    if(t->type == INT || t->type == FLOAT){
        t = nextToken();
        if(t->type == ID){
            t = nextToken();
            if(t->type == ASSIGN){
                bool e = E();
                if(e == false){
                    error("V error");
                    return e;
                }
            }
        }else{
            return false;
        }
    }

    bool p = Print();
    if(p == true){
        return p;
    }

    if(t->type == SEMICOLON){
        return true;
    }

    return false;
}



bool E(){
    bool t = T();
    bool ep = E_prime();
    if(t == false){
        error("error : coming from E.t\n");
    }
    if(ep == false){
        error("error : coming from E.ep\n");
    }

    return t * ep;

}



bool E_prime(){
    Token *operator = nextToken();
    if(operator->type == PLUS){
        bool t = T();
        bool ep = E_prime();

        if(t == false){
            error("error : coming from E_Prime.t  && PLUS BLOCK\n");
        }
        if(ep == false){
            error("error : coming from E_Prime.ep  && PLUS BLOCK\n");
        }

        return t && ep;
    }

    if(operator->type == HYPHEN){
        bool t = T();
        bool ep = E_prime();

        if(t == false){
            error("error : coming from E_Prime.t && HYPHEN BLOCK\n");
        }
        if(ep == false){
            error("error : coming from E_Prime.ep && HYPHEN BLOCK\n");
        }

        return t && ep;
    }

    if(operator->type == SEMICOLON){
        return true;
    }

    return false;
}


bool T(){
    bool f = F();
    bool tp = T_prime();

    if(f == false){
        error("error : coming from T.f\n");
    }

    if(tp == false){
        error("error : coming from T.tp \n");
    }

    return f * tp;
}


bool T_prime(){
    Token *operator = nextToken();
    if(operator->type == MUL){
        bool f= F();
        bool tp = T_prime(); 
        if(f == false){
            error("error : coming from T_Prime.t && MUL BLOCK\n");
        }

        if(tp == false){
            error("error : coming from T_Prime.tp && MUL BLOCK \n");
        }
        return f&& tp;

    }

    if(operator->type == DIVIDE){
        bool f= F();
        bool tp = T_prime(); 

        if(f == false){
            error("error : coming from T_Prime.t && DIVIDE BLOCK\n");
        }

        if(tp == false){
            error("error : coming from T_Prime.tp && DIVIDE BLOCK \n");
        }
        return f&& tp;

    }

    if(operator->type == MOD){
        bool f= F();
        bool tp = T_prime(); 

        if(f == false){
            error("error : coming from T_Prime.t && MOD BLOCK\n");
        }

        if(tp == false){
            error("error : coming from T_Prime.tp && MOD BLOCK \n");
        }

        return f&& tp;
    }

    if(operator->type == SEMICOLON){
        return true;
    }

    return false;
}

bool F(){
    Token *op = nextToken();
    if(op->type == N_BRACKETS_OPEN){
        bool e = E();
        Token *t = nextToken();
        if(t == NULL){
            error("Error coming from null token reading F\n");
            return false;
        }
        
        if(t->type == N_BRACKETS_CLOSE){
            return e;
            
        }else{
            error("Error : no closing brackets F\n");
            return false;
        }
    }

    if(op->type == ID){
        return true;
    }

    if(op->type == NUM_INT || op->type == NUM_FLOAT){
        return true;
    }

    return false;

    

}


bool IdListTail(){
    Token *t = nextToken();
    if(t->type == COMMA){
        bool idl = IdList();
        if(idl == false){
            error("Error : idtail error\n");
        } 

        return idl;

    }

    if(t->type == N_BRACKETS_CLOSE){
        return true;
        
    }else{
        return false;
    }
}

bool IdList(){
    Token *t = nextToken();
    if(t->type == ID || t->type == NUM_INT || t->type == NUM_FLOAT){

        return true;
    }else{
        error("Error : invalid idlist : IDLIST");
        return false;
    }
}

bool Print(){
    Token *t = nextToken();
    if(t->type == PRINT){
        t = nextToken();
        if(t->type == N_BRACKETS_OPEN){
            bool idl = IdList();
            if(idl == false){
                error("Error : coming from print statement : idl\n");
            }
            return idl;
        }
    }

    return false;
}




int syntaxAnalyzer(){
    bool status = Program();
    if(status == false){
        printTokenStream(nextToken());
        
    }

    return status;
}