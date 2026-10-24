#include "Node.h"
#include <stdio.h>

int main(int argc, char **argv){
    Node *n = new Node();
    Node *p = new Node();
    n->setParent(p);
    printf("parent according to parent : %p", p);
    printf("parent according to child : %p", n);
    return 0;
}