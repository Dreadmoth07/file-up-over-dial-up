#include <cstdlib>
#include <stdio.h>

char binaryToText(char *string){
    char c = strtol(string, 0, 2);
    return c;
}

void textToFile(char *string, FILE *fptr){
    char character;

    character = binaryToText(string);
    printf("%c\n", character);
    fputc(character, fptr);
}

void binaryToFile(char *fileName, char *string){
    char inpFile[] = "binary";
    FILE *sfptr;    // source file pointer
    FILE *ofptr;    // output file pointer
    bool run = true;
    char character[8]; 

    ofptr = fopen(fileName, "w");
    sfptr = fopen(inpFile, "r");

    if (ofptr == NULL)  printf("Failed to create file\n");
    else{
        while (run){
            for(int i = 0; i != 8; i++){
                character[7-i] = (char)string++;
            }
            textToFile(character, ofptr);
        }
        fclose(ofptr);
        fclose(sfptr);
    }
}


int main(){
    char test[] = "01001000";
    char fileName[] = "testFile";
    
    binaryToFile(fileName, test);

    return 0;
}