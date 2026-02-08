#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdbool.h>


int syntaxAnalyzer();
bool Program();
bool StatementList();
bool Statement();
bool VarDecl();
bool PrintStmt();
bool IdList();
bool IdListTail();
bool Expr();
bool ExprTail();
bool Term();
bool TermTail();
bool Factor();
bool Assignment();
bool isNull();

#endif