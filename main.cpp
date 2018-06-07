#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "DiGraph.hpp"
#include "Node.hpp"
#include "Edge.hpp"
#include "GraphVisualizer.hpp"
#include "SFMLGraphVisualizer.hpp"

using namespace std;

int main(){
    try{

    DiGraph g("test.txt");
    GraphVisualizer *sx = new SFMLGraphVisualizer();
    g.setVisualizer(sx);

    /*g.addNode("A",40,80);
    g.addNode("E",400,40);
    g.addNode("D",600,200);
    g.addNode("F",240,240);
    g.addNode("C",280,500);
    g.addNode("B",120,440);

    g.addEdge("A","E",10);
    g.addEdge("D","E",3);
    g.addEdge("C","D",9);
    g.addEdge("F","D",2);
    g.addEdge("B","C",7);
    g.addEdge("B","F",20);
    g.addEdge("A","B",5);
    g.addEdge("F","A",7);*/


    
    /*Liste<Edge*> path = g.dijkstraShortestPath("A","D");
    cout << path.size() << endl;
    for(int i=0;i<path.size();i++){
        cout << path[i]->getStartNode()->getKey() << " - - > " << path[i]->getEndNode()->getKey() << endl;
    }*/

    sx->hilightPath(g.dijkstraShortestPath("h1","h2"));
    sx->render(g);

    }catch(char const *ex){
        cout << "ERROR: " << ex << endl;
    }
}