#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "./../helpers/error.h"
#include "./lexer.h"
#define print(X) printf("%s\t" , X);

int tokenCount = 0;
int numberOfToken = 0;






/**
 * Checks whether a character is a delimiter that separates tokens.
 * Delimiters: space, +, -, *, /, ,, ;, %, >, <, =, (, ), {, }, [, ].
 */
bool isDelimeter(char chr){
    return (
        chr == ' ' || 
        chr == '+' ||
        chr == '-' ||
        chr == '*' ||
        chr == '/' ||
        chr == '%' ||
        chr == ',' ||
        chr == '=' ||
        chr == ';' ||
        chr == '<' ||
        chr == '>' ||
        chr == '(' ||
        chr == ')' ||
        chr == '{' ||
        chr == '}' ||
        chr == ']' ||
        chr == '[' 
    );
}

bool isBracket(char chr , Type *type){
    if(chr == '('){
        *type = N_BRACKETS_OPEN;
        return true;
    }
    if(chr == ')'){
        *type = N_BRACKETS_CLOSE;
        return true;
    }
    if(chr == '['){
        *type = R_BRACKETS_OPEN;
        return true;
    }
    if(chr == ']'){
        *type = R_BRACKETS_CLOSE;
        return true;
    }
    if(chr == '{'){
        *type = C_BRACKETS_OPEN;
        return true;
    }
    if(chr == '}'){
        *type = C_BRACKETS_CLOSE;
        return true;
    }

    return false;
}


bool isOperator(char chr , Type *type){
    if(chr == '+'){
        *type = PLUS; 
        return true;
    }
    if(chr == '-'){
        *type = HYPHEN; 
        return true;
    }
    if(chr == '/'){
        *type = DIVIDE; 
        return true;
    }
    if(chr == '*'){
        *type = MUL; 
        return true;
    }
    if(chr == '%'){
        *type = MOD; 
        return true;
    }
    if(chr == '='){
        *type = ASSIGN; 
        return true;
    }
    if(chr == '<'){
        *type = GRATER; 
        return true;
    }
    if(chr == '>'){
        *type = LOWER; 
        return true;
    }if(chr == ','){
        *type = COMMA;
        return true;
    }

    return false;
}


bool isValidIdentifier(char* str ){
    if(str == NULL) return false;
    if(!strlen(str)) return false;

    int len = strlen(str);

    int i = 0;
    while(i < len){

        bool isValid = (
            str[i] == '_' || 
            str[i] == 'a' || str[i] == 'b' || str[i] == 'c' || str[i] == 'd' || str[i] == 'e' || str[i] == 'f' ||
            str[i] == 'g' || str[i] == 'h' || str[i] == 'i' || str[i] == 'j' || str[i] == 'k' || str[i] == 'l' ||
            str[i] == 'm' || str[i] == 'n' || str[i] == 'o' || str[i] == 'p' || str[i] == 'q' || str[i] == 'r' ||
            str[i] == 's' || str[i] == 't' || str[i] == 'u' || str[i] == 'v' || str[i] == 'w' || str[i] == 'x' ||
            str[i] == 'y' || str[i] == 'z' ||
            str[i] == 'A' || str[i] == 'B' || str[i] == 'C' || str[i] == 'D' || str[i] == 'E' || str[i] == 'F' ||
            str[i] == 'G' || str[i] == 'H' || str[i] == 'I' || str[i] == 'J' || str[i] == 'K' || str[i] == 'L' ||
            str[i] == 'M' || str[i] == 'N' || str[i] == 'O' || str[i] == 'P' || str[i] == 'Q' || str[i] == 'R' ||
            str[i] == 'S' || str[i] == 'T' || str[i] == 'U' || str[i] == 'V' || str[i] == 'W' || str[i] == 'X' ||
            str[i] == 'Y' || str[i] == 'Z' || 
            str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4' || 
            str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8' || str[i] == '9' ||
            false
        );   

        if(i == 0 && isValid){
            isValid = !(
                str[i] == '0' || 
                str[i] == '1' || 
                str[i] == '2' || 
                str[i] == '3' || 
                str[i] == '4' || 
                str[i] == '5' || 
                str[i] == '6' ||  
                str[i] == '7' || 
                str[i] == '8' || 
                str[i] == '9' || 
                false);
        }
        
        if(!isValid){
            return false;
        }
    
        i++;
    }

    return true;
}


bool isKeyword(char* str , Type *type){
    const char* keywords[33] = { 
            "auto",     "break",    "case",     "char",
            "const",    "continue", "default",  "do",
            "double",   "else",     "enum",     "extern",
            "float",    "for",      "goto",     "if",
            "int",      "long",     "register", "return",
            "short",    "signed",   "sizeof",   "static",
            "struct",   "switch",   "typedef",  "union",
            "unsigned", "void",     "volatile", "while",
            "print"
    };

    const Type keywordsTypes[33] = { 
            AUTO,     BREAK,    CASE,     CHAR,
            CONST,    CONTINUE, DEFAULT,  DO,
            DOUBLE,   ELSE,     ENUM,     EXTERN,
            FLOAT,    FOR,      GOTO,     IF,
            INT,      LONG,     REGISTER, RETURN,
            SHORT,    SIGNED,   SIZEOF,   STATIC,
            STRUCT,   SWITCH,   TYPEDEF,  UNION,
            UNSIGNED, VOID,     VOLATILE, WHILE ,
            PRINT,
    };

    for(int i = 0 ; i < 33 ; i++){
        if(strcmp(keywords[i]  ,str) == 0){
            *type = keywordsTypes[i]; 
            return true;
        }
    }

    return false;
}


bool isFloat(char *str){
    if (str == NULL || *str == '\0') {
        return false;
    }

    int i = 0; 
    while (isdigit(str[i])){
        i++;
    }

    if(str[i] != '.') return false;
    i++;

    while (isdigit(str[i])){
        i++;
    }

    

    return str[i] == '\0';
}


bool isSpace(char chr){
    return chr == ' ';
}

bool isTerminator(char chr){
    return chr == ';';
}

bool isInteger(char *str){
    if (str == NULL || *str == '\0') {
        return false;
    }

    int i = 0; 
    while (isdigit(str[i])){
        i++;
    }

    return str[i] == '\0';
}


char* getSubString(char *str , int start , int end){
    int len = end - start;

    char* subString = (char *)malloc(sizeof(char) * len + 1);

    for(int i = 0 ; i < len  ; i++){
        *(subString + i) =  str[start + i];
    }

    *(subString + len ) = '\0';

    return subString;
}


int lexicalAnalyzer(char *str){
    int right = 0;
    int left = 0;
    int len = strlen(str);
  
    while(right < len && left <= right){

        if(isDelimeter(str[right]) || (right == len - 1)){

            if(right == len-1 && !isDelimeter(str[right])) right = right +1;
            char * token =  getSubString(str , left , right);
            Type keywordType;
            Type OperatorType;
            Type bracketType;
            
            if(isInteger(token)){
                // printf("INTEGER : \t%s\n" , token);
                createToken(NUM_INT , token);

            }else if(isFloat(token)){
                // printf("FLOAT : \t%s\n" , token);
                createToken(NUM_FLOAT , token);
            }else if(isKeyword(token , &keywordType)){
                // printf("KEYWORD : \t%s\n" , token);
                createToken(keywordType , token);
            }else if(isValidIdentifier(token)){
                createToken(ID , token);
            }else if(!strlen(token)){
                // pass 0 length tokens
            }else{
                error__unexpectedToken(token);
                return 0;
            }
            
            char* delimeter = getSubString(str,right , right+1);
            
            if(isOperator(str[right] , &OperatorType)){
                createToken(OperatorType , delimeter );
            }else if(isSpace(str[right])){
                // createToken(SPACE , delimeter);
                // pass all spaces
            }else if(isTerminator(str[right])){
                // printf("TERMINATOR : %c\n" , str[right]);
                createToken(SEMICOLON , delimeter);
            }else if(isBracket(str[right] , &bracketType)){
                createToken(bracketType , delimeter);
            }else{
                if(isDelimeter(str[right])){
                    printf("--UN_CAUGHT_TOKEN  : %s\n" , delimeter);
                }
            }
                
            right++;
            left = right;
            continue;
        }else{
            right++;
        }
    }

    // printTokens();

    return 1;
}



Token * tokenStack = NULL;
Token *tos = NULL;




void pushToTokenStack(Token *token){
    if(tokenStack == NULL){
        tokenStack = token;
    }else{
        tos->next = token;
    }

    tos = token;
}



Token *next = NULL;
bool headMoved = false;
Token* nextToken(){
    if(0 < tokenCount )tokenCount -- ;
    if(next == NULL && tokenStack == NULL) return NULL;

    if(next == NULL && tokenStack != NULL && !headMoved ) {
        next = tokenStack;
        headMoved = true;
        return next;
    }else{
        if(next == NULL) return NULL;
        // printf("%s %p" , next->value , next);
        next = next->next;
        return next;


    }

    


}

Token* previousToken(){
    if(next == NULL) return NULL;
    if(0 < tokenCount )tokenCount ++ ;
    if(next->previous == NULL) return NULL;
    next = next->previous;
    return next;
    

}



Token *saved = NULL;
int savedCount = 0;
bool headStatus =  true;

void tokenSave(){
    int i = 1;
    saved = tokenStack;
    savedCount = tokenCount + 1;
    int tokenIndex = numberOfToken - savedCount;
    if(tokenIndex == -1 ) {
        next = NULL;
        headMoved = false;
        headStatus = headMoved;
        saved = NULL;
        savedCount = 0;
    }else if(tokenIndex == 0){
        saved = tokenStack;
        savedCount = numberOfToken;
    }
    
    while(i < tokenIndex ){
        saved = saved->next;  
        i++;
    }
}

void tokenRollback(){
    next = saved;
    tokenCount = savedCount;
    headMoved = headStatus;
}


void printTokens(){
    Token *t = tokenStack;
    while(1){
        if(t == NULL) return;
        printf("TOKEN: \t");
        switch (t->type){
            case SPACE: print("SPACE") break;
            case PLUS:  print("PLUS")  break;
            case HYPHEN:print("MINUS") break;
            case MUL:print("MUL") break;
            case DIVIDE:print("DIVIDE") break;
            case MOD:print("MOD") break;
            case COMMA:print("COMMA") break;
            case ASSIGN:print("ASSIGN") break;
            case SEMICOLON:print("SEMICOLON") break;
            case GRATER:print("GRATER") break;
            case LOWER:print("LOWER") break;
            case N_BRACKETS_OPEN:print("N_BRACKETS_OPEN") break;
            case N_BRACKETS_CLOSE:print("N_BRACKETS_CLOSE") break;
            case C_BRACKETS_OPEN:print("C_BRACKETS_OPEN") break;
            case C_BRACKETS_CLOSE:print("C_BRACKETS_CLOSE") break;
            case R_BRACKETS_OPEN:print("R_BRACKETS_OPEN") break;
            case R_BRACKETS_CLOSE:print("R_BRACKETS_CLOSE") break;
            case INT:print("INT") break;
            case FLOAT:print("FLOAT") break;
            case WHILE:print("WHILE") break;
            case CASE:print("CASE") break;
            case LONG:print("LONG") break;
            case FOR:print("FOR") break;
            case IF:print("IF") break;
            case ELSE:print("ELSE") break;
            case DEFAULT:print("DEFAULT") break;
            case DO:print("DO") break;
            case ENUM:print("ENUM") break;
            case RETURN:print("RETURN") break;
            case CONST:print("CONST") break;
            case SHORT:print("SHORT") break;
            case STRUCT:print("STRUCT") break;
            case DOUBLE:print("DOUBLE") break;
            case AUTO:print("AUTO") break;
            case BREAK:print("BREAK") break;
            case CHAR:print("CHAR") break;
            case CONTINUE:print("CONTINUE") break;
            case EXTERN:print("EXTERN") break;
            case VOID:print("VOID") break;
            case UNION:print("UNION") break;
            case STATIC:print("STATIC") break;
            case REGISTER:print("REGISTER") break;
            case SIGNED:print("SIGNED") break;
            case TYPEDEF:print("TYPEDEF") break;
            case SIZEOF:print("SIZEOF") break;
            case SWITCH:print("SWITCH") break;
            case UNSIGNED:print("UNSIGNED") break;
            case VOLATILE:print("VOLATILE") break;
            case LETTER:print("LETTER") break;
            case GOTO:print("GOTO") break;
            case ID:print("ID") break;
            case NUM_INT:print("NUM_INT") break;
            case NUM_FLOAT:print("NUM_FLOAT") break;
            case PRINT:print("PRINT") break;
        }
        
        printf("%s\n" ,t->value);
        t = t->next;
    }
}


void printTokenStream(Token *stopToken){
    Token *t = tokenStack;
    while(1){
        if(t == NULL) return;
        if(t == stopToken){
            break;
        }

        if(t->type != SEMICOLON){
            printf("%s" ,t->value);
        }else{
            printf("%s\n" ,t->value);
        }
        t = t->next;
    }
}


    // SPACE = 0 , // ' '
    // PLUS = 1, // '+'
    // HYPHEN = 2, // '-'
    // MUL = 3, // '*'
    // DIVIDE = 4, // '/'
    // MOD = 5, // '%'
    // COMMA = 6, // ','
    // ASSIGN = 7, // '='
    // SEMICOLON = 8, // ';'
    // GRATER = 9, // '<'
    // LOWER = 10, // '>'
    // N_BRACKETS_OPEN = 11, // '('
    // N_BRACKETS_CLOSE = 12, // ')'
    // R_BRACKETS_OPEN = 13, // '['
    // R_BRACKETS_CLOSE = 14, // ']'
    // C_BRACKETS_OPEN = 15, // '{'
    // C_BRACKETS_CLOSE = 16, // '}'
    // INT = 17 ,
    // FLOAT = 18 ,
    // WHILE = 19 ,
    // LONG = 20,
    // FOR = 21,
    // IF = 22 , 
    // ELSE = 23 ,
    // CASE  = 24 , 
    // DEFAULT = 25, 
    // DO = 26 ,
    // ENUM = 27,
    // RETURN = 28,
    // CONST  = 29 , 
    // SHORT = 30,
    // STRUCT = 31 , 
    // DOUBLE = 32,
    // AUTO = 33,
    // BREAK = 34,
    // CASE = 35,
    // CHAR = 36,
    // CONTINUE = 37,
    // EXTERN = 38,
    // VOID = 39,
    // UNION = 40,
    // STATIC = 41,
    // REGISTER = 42,
    // SIGNED = 43 , 
    // TYPEDEF = 44,
    // SIZEOF = 45,
    // SWITCH = 46 ,
    // UNSIGNED = 47,
    // VOLATILE = 48,
    // LETTER = 49,



Token* createToken(Type type , char* value ){
    Token *t = (Token *)malloc(sizeof(Token));
    t->type = type;
    t->value = value;
    t->next = NULL;
    t->previous = tos;
    pushToTokenStack(t);
    tokenCount++;
    numberOfToken = tokenCount;
    return t;
}




bool islastToken(){
    return tokenCount == 0;
}

bool getTokenNumber(){
    return tokenCount;
}