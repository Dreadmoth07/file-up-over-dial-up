#include <string.h>
#include <stdio.h>
#include <cstdlib>

int space_index(char *morse){
    int index = 0;
    for (; *morse != '\n' && *morse != ' '; morse++) index++;
    return index;
}

void string_parse(char *morse, int index, char *parsed_string){
    for(int i = 0; i != index; i++){
        parsed_string[i] = *morse;
        morse++;
    }
    parsed_string[index] = '\0';
}

int main(){
    char test[] = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --..\n";

    int test_space = space_index(test);

    char *parsed_string = (char *)malloc(test_space + 1);
    string_parse(test, test_space, parsed_string);

    printf("%d  %s\n", test_space, parsed_string);

    free(parsed_string);
    return 0;
}