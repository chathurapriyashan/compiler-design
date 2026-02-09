
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
