#pragma once

#include <string>

#include "Node.hpp"

class Edge{
    private:
        Node *startnode;
        Node *endnode;
        float weight;
    public:
        Edge(Node *startnode, Node *endnode, float weight);

        float getWeight();
        Node *getStartNode();
        Node *getEndNode();

        void setWeight(float w);
        void setStartNode(Node *n);
        void setEndNode(Node *n);
};