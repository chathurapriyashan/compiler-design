#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdbool.h>


int syntaxAnalyzer();
void Program();
void StatementList();
void Statement();
void VarDecl();
void Assignment();
void PrintStmt();
void IdList();
void IdListTail();
int Expr();
int ExprTail();
int Term();
int TermTail();
int Factor();

#endif