#include "Node.h"

Node* Node::getParent(){
    return parent;
}
Node* Node::getDot(){
    return dotChild;
}
Node* Node::getDash(){
    return dashChild;
}
void Node::setParent(Node* newParent){
    free(parent);
    parent = newParent;
}
