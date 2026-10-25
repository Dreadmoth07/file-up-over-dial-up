#include <cstdlib>
#include <stdio.h>

char binaryToText(char *string){
    char c = strtol(string, 0, 2);
    return c;
}

void textToFile(char *string, FILE *fptr){
    char character;
    character = binaryToText(string);
    fputc(character, fptr);
}

void binaryToFile(char *fileName, char *string){
    char inpFile[] = "binary";
    FILE *sfptr;    // source file pointer
    FILE *ofptr;    // output file pointer
    char character[9]; 

    ofptr = fopen(fileName, "w");
    sfptr = fopen(inpFile, "r");

    if (ofptr == NULL)  printf("Failed to create file\n");
    else{
        char data[9];
        while (fgets(data, 9, sfptr) != NULL){
            textToFile(data, ofptr);
        }
        fclose(ofptr);
        fclose(sfptr);
    }
}