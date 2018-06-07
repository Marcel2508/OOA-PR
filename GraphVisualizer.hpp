#pragma once
#include "Liste.hpp"
#include "Edge.hpp"

class DiGraph;

class GraphVisualizer{
    protected:
        Liste<Edge*> hilightedPath;
    public:
    virtual void render(DiGraph &g)=0;
    virtual void show()=0;
    virtual void hilightPath(Liste<Edge*> path)=0;
};