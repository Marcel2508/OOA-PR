#include <string>

#include "Node.hpp"
#include "Edge.hpp"

using namespace std;

Node::Node(string key, int x, int y){
    this->node_key=key;
    this->position_x=x;
    this->position_y=y;
}
        
std::string Node::getKey(){
    return this->node_key;
}
int Node::getPositionX(){
    return this->position_x;
}
int Node::getPositionY(){
    return this->position_y;
}

Liste<Edge*> Node::getEdges(){
    return this->edges;
}

void Node::setKey(std::string new_key){
    this->node_key=new_key;
}
void Node::setPositionX(int x){
    this->position_x=x;
}
void Node::setPositionY(int y){
    this->position_y=y;
}
void Node::setNewEdge(Edge *edge){
    this->edges.append(edge);
}