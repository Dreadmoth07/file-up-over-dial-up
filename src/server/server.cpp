#include "server.h"
#include <cstdio>

void ServeRequest(){
    std::cout << "getting binary" << std::endl;
    reciever(); // takes in mic input and turns it into a binary file.
    char rq[] = "request";

    binaryToFile(rq); // convert binary file into readable ascii

    std::cout << "Got request" << std::endl;
    // get the actual request
    FILE* f = fopen("request","r");
    char c = fgetc(f), tmp='0';
    while(c != EOF){ // move pointer to where the file name THEORETICALLY starts
        if(tmp == ':' && c == ' '){
            break;
        }
        tmp = c;
        c = fgetc(f);
    }
    
    int i=0;
    char fpBuffer[BUFFER_LEN];
    while(c!=' ' && c !=EOF){
        fpBuffer[i] = c;
        i++;
        c = fgetc(f);
    }

    fpBuffer[i] = '\0'; // end file path buffer

    std::cout << fpBuffer << std::endl;

    fileToBeep(fpBuffer); // beep the file

}

int main(int argc, char** argv){
    ServeRequest();
}