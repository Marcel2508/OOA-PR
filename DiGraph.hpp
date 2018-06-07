#pragma once

#include <string>
#include <fstream>

#include "GraphVisualizer.hpp"
#include "Node.hpp"
#include "Liste.hpp"
#include "Edge.hpp"


class GraphVisualizer;

class DiGraph{
    private:
        Liste<Node*> nodes;
        int indexOf(Node*);
        GraphVisualizer *graphviz;
    public:
        DiGraph(std::string filename);
        void addNode(Node *node);
        void addNode(std::string key,int x,int y);
        void addEdge(std::string key1, std::string key2, float weight);
        Liste<Node*> getNeighbours(std::string key);
        Liste<Edge*> getEdges(std::string key);
        Liste<Node*> getNodes();
        Liste<Edge*> dijkstraShortestPath(std::string start, std::string end);
        void setVisualizer(GraphVisualizer *graphviz);
        GraphVisualizer *getVisualizer();
};