#include <stdio.h>
#include <stdbool.h>
#include "./src/lexer/lexer.h"
#include "./src/helpers/files.h"

int main(int argc , char** args){
    if(argc <= 1){
        printf("Error: no input files found\n");
        return 1;
    }
    
    char* content = getFileContent(args[1]);
    printf("\n\n%s\n\n" , content);

    int lexerStatus = lexicalAnalyzer(content);    
}