#include "client.h"
#include <cstdio>

void constructRequest(char* filepath){
    FILE* r = fopen("./request","w");

    fputs("Can I haz: ", r);
    fputs(filepath, r);
    fputs(" k?",r);

    fclose(r);
}


void makeRequest(){
    char request[] = "./request";
    fileToBeep(request);
}

void recieveFile(char* endFileName){
    reciever();
    binaryToFile(endFileName);
}

int main(int argc, char** argv){
    char filepath[] = "/test.txt";
    constructRequest(filepath);
    makeRequest();

    recieveFile(filepath);
}