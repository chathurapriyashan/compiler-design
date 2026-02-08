#include <stdio.h>
#include <stdbool.h>
#include "./src/lexer/lexer.h"
#include "./src/helpers/files.h"
#include "./src/syntax/syntax.h"

int main(int argc , char** args){
    if(argc <= 1){
        printf("Error: no input files found\n");
        return 1;
    }
    
    char* content = getFileContent(args[1]);

    int lexerStatus = lexicalAnalyzer(content);
    printTokens();   
    if(lexerStatus) printf("✅ Lexical Analysis Completed\n"); 
    else printf("🚫 Lexical Analysis Failed\n"); 

    if(!lexerStatus) return 1;


    int syntaxStatus = syntaxAnalyzer(); 

    if(syntaxStatus) printf("✅ Syntax Analysis Completed\n"); 
    else printf("🚫 Syntax Analysis Failed\n"); 

    if(!syntaxStatus) return 1;

    return 0;
    


}