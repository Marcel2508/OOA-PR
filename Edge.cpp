#include "Edge.hpp"


Edge::Edge(Node *startnode, Node *endnode, float weight){
    this->startnode=startnode;
    this->endnode=endnode;
    this->weight=weight;
}
        
float Edge::getWeight(){
    return this->weight;
}
Node *Edge::getStartNode(){
    return this->startnode;
}
Node *Edge::getEndNode(){
    return this->endnode;
}

void Edge::setWeight(float w){
    this->weight=w;
}
void Edge::setStartNode(Node *n){
    this->startnode=n;
}
void Edge::setEndNode(Node *n){
    this->endnode=n;
}