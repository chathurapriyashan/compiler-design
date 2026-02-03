#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "./../helpers/error.h"


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


bool isOperator(char chr){
    return (
        chr == '+' ||
        chr == '-' ||
        chr == '/' ||
        chr == '*' ||
        chr == '<' ||
        chr == '>' ||
        chr == '=' ||
        chr == '%' 
    );
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


bool isKeyword(char* str){
    const char* keywords[32] = { 
            "auto",     "break",    "case",     "char",
            "const",    "continue", "default",  "do",
            "double",   "else",     "enum",     "extern",
            "float",    "for",      "goto",     "if",
            "int",      "long",     "register", "return",
            "short",    "signed",   "sizeof",   "static",
            "struct",   "switch",   "typedef",  "union",
            "unsigned", "void",     "volatile", "while" 
    };

    for(int i = 0 ; i < 32 ; i++){
        if(strcmp(keywords[i]  ,str) == 0){
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
    int len = end - start + 1;
    char* subString = (char *)malloc(sizeof(char) * len);
    for(int i = 0 ; i < len - 1 ; i++){
        *(subString + i) =  str[start + i];
    }

    *(subString + len) = '\0';

    return subString;
}


int lexicalAnalyzer(char *str){
    int right = 0;
    int left = 0;
    int len = strlen(str);
  
    while(right < len && left <= right){

        if(isDelimeter(str[right])){

            char * token = getSubString(str , left , right);
            
            
            if(isInteger(token)){
                printf("INTEGER : \t%s\n" , token);
            }else if(isFloat(token)){
                printf("FLOAT : \t%s\n" , token);
            }else if(isKeyword(token)){
                printf("KEYWORD : \t%s\n" , token);
            }else if(isValidIdentifier(token)){
                printf("IDENTIFIER : \t%s\n" , token);
            }else if(!strlen(token)){
                // pass 0 length tokens
            }else{
                error__unexpectedToken(token);
                return 1;
            }
            
            
            if(isOperator(str[right])){
                printf("OPERATOR : \t%c\n" , str[right]);
            }else if(isSpace(str[right])){
                // pass all spaces
            }else if(isTerminator(str[right])){
                printf("TERMINATOR : %c\n" , str[right]);
            }else{
                printf("DELIMETER : %c\n" , str[right]);
            }
                
            right++;
            left = right;
            continue;
        }else{
            right++;
        }
    }

    return 0;
}
