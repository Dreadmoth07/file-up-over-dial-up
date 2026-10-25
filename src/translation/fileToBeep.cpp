#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <math.h>


void beep(char *string){
    for(int i = strlen(string); i >= 0; i--){
        if (*string == '1') printf("\a\n");
        string++;
        usleep(150000);
    }
}

void fileToBeep(char *name){
    FILE* fptr;
    fptr = fopen(name, "r");
    int character;
    char str[9];

    char data[2];
    if (fptr == NULL) printf("Failed to open\n");
    else{
        while (fgets(data, 2, fptr) != NULL){
            character = 0;
            for(int i = 7; i >= 0; i--){
                int bit = (*data >> i) & 1;
                character += (bit * pow(10, i));
            }
            
            sprintf(str, "%d", character);

            if (strlen(str) != 8){
                int distance = 8 - strlen(str);
                char str2[9] = "";

                for(int i = 0; distance - i != 0; i++) str2[i] = '0';
                strcat(str2, str);

                printf("%s\n", str2);
                beep(str2);
            } else{
                printf("%s\n", str);
                beep(str);
            }
        }   
        fclose(fptr);
    }
}


int main(){
    char test[] = "01001000 01100101 01101100 01101100 01101111 00100000 01110111 01101111 01110010 01101100 01100100\0";
    char file[] = "testFile";
    fileToBeep(file);
    return 0;
}