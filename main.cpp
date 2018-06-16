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

    sx->render(g);

    }catch(char const *ex){
        cout << "ERROR: " << ex << endl;
    }
}