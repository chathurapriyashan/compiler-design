#include <stdio.h>
#include <stdlib.h>

char* getFileContent(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    if (fseek(fp, 0L, SEEK_END) != 0) { 
        perror("Error seeking to end of file");
        fclose(fp);
        return NULL;
    }

    long size = ftell(fp);
    if (size == -1L) {
        perror("Error getting file position");
        fclose(fp);
        return NULL;
    }
    
    fclose(fp);
    
    fp = fopen(filename , "r");
    char *content = (char *)malloc(size + 1);
    char ch;

    int i = 0;
    while ((ch = fgetc(fp)) != EOF){
        if(ch == '\n') continue;
        *(content + i) = ch;
        i++;
    }

    fclose(fp);

    *(content + i) = '\0';

    return content;
    
    
}


