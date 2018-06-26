#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <sstream>
#include <iostream>
#define NODERADIUS 30

#include "DiGraph.hpp"
#include "Edge.hpp"
#include "Node.hpp"
#include "Liste.hpp"
#include "GraphVisualizer.hpp"

using namespace std;
class SFMLGraphVisualizer : public GraphVisualizer
{
  private:
    sf::RenderWindow window;
    sf::Font font;
    bool isHilighted(Edge *edge){
        for(int i=0;i<this->hilightedPath.size();i++){
            if(edge->getStartNode()->getKey()==this->hilightedPath[i]->getStartNode()->getKey() &&  edge->getEndNode()->getKey()==this->hilightedPath[i]->getEndNode()->getKey()){
                return true;
            }
        }
        return false;
    }

    ///////////////////
    int offsetX;
    int offsetY;
    Node *selectedRef=0;

    void onMouseMoved(DiGraph &g, int x,int y){
        if(this->selectedRef==0)return;
        this->selectedRef->setPositionX(x+this->offsetX);
        this->selectedRef->setPositionY(y+this->offsetY);
    };
    void onMouseDown(DiGraph &g, int x,int y){
        Liste<Node*> *listCopy = g.getNodesRef();
        int tx,ty;
        cout << x << ", " << y << endl;
        for(int i=0;i<listCopy->size();i++){
            tx = (*listCopy)[i]->getPositionX();
            ty = (*listCopy)[i]->getPositionY();
            if(
                x >= tx-NODERADIUS &&
                y >= ty-NODERADIUS &&
                x <= tx + NODERADIUS &&
                y <= ty + NODERADIUS
            ){
                this->offsetX=tx-x;
                this->offsetY=ty-y;
                this->selectedRef=(*listCopy)[i];
                return;
            }
        }
    };
    void onMouseUp(DiGraph &g, int x,int y){
        if(this->selectedRef==0)return;
        this->selectedRef=0;
    };
    ///////////////

  public:
    SFMLGraphVisualizer()
    {
        // load my font
        this->font.loadFromFile("arial.ttf");
    }
    void render(DiGraph &g)
    {
        window.create(sf::VideoMode(900, 600), "myGraph");
        Liste<Node *> nodes = g.getNodes();
        while (window.isOpen())
        {
            // Process events
            sf::Event event;
            while (window.pollEvent(event))
            {
                // Close window : exit
                if (event.type == sf::Event::Closed)
                    window.close();
                else if(event.type==sf::Event::MouseButtonPressed)
                    this->onMouseDown(g,event.mouseButton.x,event.mouseButton.y);
                else if(event.type==sf::Event::MouseButtonReleased)
                    this->onMouseUp(g,event.mouseButton.x,event.mouseButton.y);
                else if(event.type==sf::Event::MouseMoved)
                    this->onMouseMoved(g,event.mouseMove.x,event.mouseMove.y);
            }
            // Clear screen
            window.clear(sf::Color::White);
            for (unsigned int i = 0; i < nodes.size(); i++)
            {   
                Node *node = nodes.getValueAt(i);
                sf::Color color(255, 0, 0);
                drawNode(*node, color);
                // Ausgehende Kanten einzeichnen
                Liste<Edge *> edges = g.getEdges(node->getKey());
                for (unsigned int j = 0; j < edges.size(); j++)
                {
                    
                    drawEdge(*(edges.getValueAt(j)), sf::Color::Black, edges.getValueAt(j)->getWeight(), 1);
                }
            }
            // Update the window
            window.display();
        }
    }

    void show(){

    }
    void hilightPath(Liste<Edge*> path){
        this->hilightedPath = path;
    }

    void drawNode(Node &node, sf::Color nodeColor)
    {
        sf::CircleShape Circle(NODERADIUS);
        Circle.setPosition(node.getPositionX() - NODERADIUS, node.getPositionY() - NODERADIUS);
        Circle.setFillColor(sf::Color::White);
        Circle.setOutlineColor(nodeColor);
        Circle.setOutlineThickness(5);

        window.draw(Circle);
        sf::Text Label(node.getKey(), font, 32);
        Label.setPosition(node.getPositionX() - NODERADIUS / 2 + 5, node.getPositionY() - NODERADIUS / 2 - 5);
        //Label.setFillColor(sf::Color::Blue);
        Label.setColor(sf::Color::Blue);
        window.draw(Label);
    }

    void drawEdge(Edge &edge, sf::Color color, double weight, int thickness = 1, int arrowMagnitude = 20)
    {

        sf::Vector2f p(edge.getStartNode() -> getPositionX(), edge.getStartNode() -> getPositionY());
        sf::Vector2f q(edge.getEndNode() -> getPositionX(), edge.getEndNode() -> getPositionY());

        // Berechne den Winkel
        const double PI = 3.141592653;
        double angle = atan2((double)p.y - q.y, (double)p.x - q.x);

        // Berechne verkuerzten Pfeil
        q.x = (int)(q.x + NODERADIUS * cos(angle));
        q.y = (int)(q.y + NODERADIUS * sin(angle));
        p.x = (int)(p.x - NODERADIUS * cos(angle));
        p.y = (int)(p.y - NODERADIUS * sin(angle));
        if(isHilighted(&edge))color=sf::Color::Red;
        sf::Vertex line[2] = {
                sf::Vertex(sf::Vector2f(p.x, p.y), color),
                sf::Vertex(sf::Vector2f(q.x, q.y), color)
        };

        // thickness
        window.draw(line, 2, sf::Lines);
        std::stringstream weightstring;
        weightstring << weight;
        sf::Text Labelweight(weightstring.str(), font, 32);
        int size = sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
        Labelweight.setPosition(p.x - (size / 2) * cos(angle) + 10 * sin(angle), p.y - (size / 2) * sin(angle) + 10 * cos(angle));
        Labelweight.setColor(sf::Color::Blue);
        window.draw(Labelweight);
        // Erstes Segment
        p.x = (int)(q.x + arrowMagnitude * cos(angle + PI / 8));
        p.y = (int)(q.y + arrowMagnitude * sin(angle + PI / 8));
        sf::Vertex first[2] = {
                sf::Vertex(sf::Vector2f(p.x, p.y), color),
                sf::Vertex(sf::Vector2f(q.x, q.y), color)
        };
        window.draw(first, 2, sf::Lines);

        // Zweites Segment
        p.x = (int)(q.x + arrowMagnitude * cos(angle - PI / 8));
        p.y = (int)(q.y + arrowMagnitude * sin(angle - PI / 8));
        sf::Vertex second[2] = {
                sf::Vertex(sf::Vector2f(p.x, p.y), color),
                sf::Vertex(sf::Vector2f(q.x, q.y), color)
        };
        window.draw(second, 2, sf::Lines);
    }
};