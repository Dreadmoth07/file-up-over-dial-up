#include <cstdlib>
#include <stdio.h>
#include <string.h>

char binaryToText(char *string){
    char c = strtol(string, 0, 2);
    return c;
}

void textToFile(char *string, FILE *fptr){
    char character;
    character = binaryToText(string);
    fputc(character, fptr);
}

void binaryToFile(char *fileName){
    char inpFile[] = "binary";
    FILE *sfptr;    // source file pointer
    FILE *ofptr;    // output file pointer

    ofptr = fopen(fileName, "w");
    sfptr = fopen(inpFile, "r");

    if (ofptr == NULL || sfptr == NULL )  printf("Failed to create file\n");
    else{
        char data[9];
        while (fgets(data, 9, sfptr) != NULL) {
            if(strlen(data) == 8) textToFile(data, ofptr);
        }
        
        fclose(ofptr);
        fclose(sfptr);
    }
}