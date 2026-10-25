#include "client.h"
#include <cstdio>

void constructRequest(const char* filepath){
    FILE* r = fopen("./request","w");

    fputs("Can I haz: ", r);
    fputs(filepath, r);
    fputs(" k?",r);

    fclose(r);
}

void makeRequest(){
    fileToBeep("./request");
}

void recieveFile(const char* endFileName){
    reciever();
    binaryToFile(endFileName);
}

int main(int argc, char** argv){
    constructRequest("/test.txt");
    makeRequest();

    recieveFile("test.txt");
}