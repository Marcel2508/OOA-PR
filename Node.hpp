#pragma once

#include <string>

#include "Liste.hpp"
class Edge;

class Node{
    private:
        std::string node_key;
        int position_x;
        int position_y;
        Liste<Edge*> edges;
    public:
        Node(std::string key, int x, int y);

        std::string getKey();
        int getPositionX();
        int getPositionY();
        Liste<Edge*> getEdges();

        void setKey(std::string new_key);
        void setPositionX(int x);
        void setPositionY(int y);
        void setNewEdge(Edge *edge);

};