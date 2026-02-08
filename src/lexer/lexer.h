#ifndef LEXER_H
// #define SPACE   0   // ' '
// #define PLUS   1  // '+'
// #define HYPHEN   2  // '-'
// #define MUL   3  // '*'
// #define DIVIDE   4  // '/'
// #define MOD   5  // '%'
// #define COMMA   6  // ' '
// #define ASSIGN   7  // ' '
// #define SEMICOLON   8  // ';'
// #define GRATER   9  // '<'
// #define LOW   10  // '>'
// #define N_BRACKETS_OPEN   11  // '('
// #define N_BRACKETS_CLOSE   12  // ')'
// #define R_BRACKETS_OPEN   13  // '['
// #define R_BRACKETS_CLOSE   14  // ']'
// #define C_BRACKETS_OPEN   15  // '{'
// #define C_BRACKETS_CLOSE   16  // '}'
// #define INT   17  
// #define FLOAT   18  
// #define WHILE   19  
// #define LONG   20 
// #define FOR   21 
// #define IF   22   
// #define ELSE   23  
// #define CASE    24   
// #define DEFAULT   25  
// #define DO   26  
// #define ENUM   27 
// #define RETURN   28 
// #define CONST    29   
// #define SHORT   30 
// #define STRUCT   31   
// #define DOUBLE   32 
// #define AUTO   33 
// #define BREAK   34 
// #define CASE   35 
// #define CHAR   36 
// #define CONTINUE   37 
// #define EXTERN   38 
// #define VOID   39 
// #define UNION   40 
// #define STATIC   41 
// #define REGISTER   42 
// #define SIGNED   43   
// #define TYPEDEF   44 
// #define SIZEOF   45 
// #define SWITCH   46  
// #define UNSIGNED   47 
// #define VOLATILE   48 
// #define LETTER   49 
typedef enum {
        SPACE = 0 , // ' '
        PLUS = 1, // '+'
        HYPHEN = 2, // '-'
        MUL = 3, // '*'
        DIVIDE = 4, // '/'
        MOD = 5, // '%'
        COMMA = 6, // ','
        ASSIGN = 7, // '='
        SEMICOLON = 8, // ';'
        GRATER = 9, // '<'
        LOWER = 10, // '>'
        N_BRACKETS_OPEN = 11, // '('
        N_BRACKETS_CLOSE = 12, // ')'
        R_BRACKETS_OPEN = 13, // '['
        R_BRACKETS_CLOSE = 14, // ']'
        C_BRACKETS_OPEN = 15, // '{'
        C_BRACKETS_CLOSE = 16, // '}'
        INT = 17 ,
        FLOAT = 18 ,
        WHILE = 19 ,
        LONG = 20,
        FOR = 21,
        IF = 22 , 
        ELSE = 23 ,
        CASE  = 24 , 
        DEFAULT = 25, 
        DO = 26 ,
        ENUM = 27,
        RETURN = 28,
        CONST  = 29 , 
        SHORT = 30,
        STRUCT = 31 , 
        DOUBLE = 32,
        AUTO = 33,
        BREAK = 34,
        CHAR = 35,
        CONTINUE = 36,
        EXTERN = 37,
        VOID = 38,
        UNION = 39,
        STATIC = 40,
        REGISTER = 41,
        SIGNED = 42 , 
        TYPEDEF = 43,
        SIZEOF = 44,
        SWITCH = 45 ,
        UNSIGNED = 46,
        VOLATILE = 47,
        LETTER = 48,
        GOTO = 49,
        ID = 50,
        NUM_INT = 51,
        NUM_FLOAT = 52,
        PRINT = 53,
    } Type;



typedef struct token{
    Type type;
    char *value;
    struct token *next;
    struct token *previous;
} Token;


bool isDelimeter(char chr);
bool isOperator(char chr , Type *type);
bool isValidIdentifier(char* str );
int lexicalAnalyzer(char *str);
Token* createToken(Type type , char* value );
void printTokens();
void printTokenStream(Token *stopToken);
void pushToTokenStack(Token *token);
Token* nextToken();
bool islastToken();
void tokenSave();
void tokenRollback();
Token* previousToken();













#define LEXER_H
#endif