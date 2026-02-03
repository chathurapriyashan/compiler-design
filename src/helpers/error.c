#include "error.h"
#include "stdio.h"

void error__unexpectedToken(char * token){
    printf("Unexpected Token :  %s\n" , token);
    perror("Invalid Token Detected\n");
}