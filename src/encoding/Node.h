#include <stdlib.h>

class Node;

class Node{
    private:
        char state[8];
        Node *parent, *dotChild, *dashChild;
    public:
        char* getState();
        Node* getParent();
        Node* getDot();
        Node* getDash();
        void setParent(Node*);
};
