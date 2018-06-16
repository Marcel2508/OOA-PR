#include <limits>
#include <iostream>
#include <cstdlib>
#include "DiGraph.hpp"
#include "PriorityQueue.hpp"
#include "GraphVisualizer.hpp"
#include "tokenizer.hpp"

using namespace std;

bool isInt(std::string v){
    return !(atoi(v.c_str())==0 && v[0]!='0');
}

DiGraph::DiGraph(std::string filename){
    ifstream file(filename.c_str());
    string curLine;
    if(file.is_open()){
        int lc = 0;
        while(getline(file,curLine)){
            lc++;
            Tokenizer toks(curLine," ");
            if(toks.countTokens()==3){
                string ft = toks.nextToken();
                string st = toks.nextToken();
                string lt = toks.nextToken();
                if(!isInt(st)){
                    //KEINE NUMMER (KANTE)
                    try{
                        this->addEdge(ft,st,atof(lt.c_str()));   
                    }
                    catch(int ex){
                        cout << "Line" << lc << " invalid Node Names. Skipping!" << endl;
                    }
                }
                else{
                    //KNOTEN:
                    if(isInt(lt))
                        this->addNode(ft,atoi(st.c_str()),atoi(lt.c_str()));
                    else{
                        cout << "Line " << lc << " invalid int. Skipping!" << endl;
                    }
                }
            }else{
                cout << "Line " << lc << " invalid. Skipping!" << endl;
            }
        }
        file.close();
    }
    else{
        cout << "File not found!" << endl;
        exit(1);
    }
}

void DiGraph::addNode(Node *node){
    this->nodes.append(node);
}

void DiGraph::addNode(std::string key,int x,int y){
    this->nodes.append(new Node(key,x,y));
}

void DiGraph::addEdge(std::string key1, std::string key2, float weight){
    string k = "";
    Node *n1=0;
    Node *n2=0;
    for(int i=0;i<this->nodes.size();i++){
        k=nodes.getValueAt(i)->getKey();
        if(k==key1)n1=nodes.getValueAt(i);
        if(k==key2)n2=nodes.getValueAt(i);
    }
    Edge *e = new Edge(n1,n2,weight);
    if(n1!=0)n1->setNewEdge(e);
    else throw 121;
}
Liste<Node*> DiGraph::getNeighbours(std::string key){
    Liste<Node*> nl;
    Node *n;
    Liste<Edge*> el;
    for(int i=0;i<this->nodes.size();i++){
        n=nodes.getValueAt(i);
        if(n->getKey()==key){
            el = n->getEdges();
            for(int j=0;j<el.size();j++){
                nl.append(el.getValueAt(j)->getEndNode());
            }
        }
    }
    return nl;
}
Liste<Edge*> DiGraph::getEdges(std::string key){
    Liste<Node*> nl;
    Node *n;
    Liste<Edge*> el;
    for(int i=0;i<this->nodes.size();i++){
        n=nodes.getValueAt(i);
        if(n->getKey()==key){
            return n->getEdges();
        }
    }
    throw 404;
}
Liste<Node*> DiGraph::getNodes(){
    return this->nodes;
}
Liste<Node*> *DiGraph::getNodesRef(){
    return &(this->nodes);
}

int DiGraph::indexOf(Node* n){
    for(int j=0;j<this->nodes.size();j++){if(this->nodes.getValueAt(j)->getKey()==n->getKey())return j;}
    return -1;
}

Liste<Edge*> DiGraph::dijkstraShortestPath(std::string start, std::string end){
    Liste<Edge*> tmp;
    int used = this->nodes.size();
    PriorityQueue<Node*> pq;

    float *dist = new float[used];
    Node **prev = new Node*[used];

    for(int i=0; i< used;i++){
        if(this->nodes.getValueAt(i)->getKey()==start){
            dist[i]=0;
        }
        else{
            dist[i]=9999999;//std::numeric_limits<float>::infinity();
        }
        prev[i]=NULL;
        pq.insert(this->nodes.getValueAt(i),dist[i]);
    }


    while(pq.hasValue()){
        Node *u = pq.getMinValue();
        Liste<Edge*> outEdges = u->getEdges();
        int size = outEdges.size();
        pq.extractMin();
        for(int i=0;i<size;i++){
            Node *v = outEdges.getValueAt(i)->getEndNode();
            //dist[u]
            float alt = dist[this->indexOf(u)]+outEdges.getValueAt(i)->getWeight();

            int iov = this->indexOf(v);
            if(alt<dist[iov]){
                dist[iov]=alt;
                prev[iov]=u;
                pq.decreaseKey(v,alt);
            }

        }
    }

    int tt = -1;
    for(int i=0;i<used;i++){if(this->nodes[i]->getKey()==end)tt=i;} // FEHLER!!!
    if(tt==-1)return tmp;
    Node *u=this->nodes[tt];


    while(prev[this->indexOf(u)]!=NULL){
        Node *p = prev[this->indexOf(u)];
        for(int i=0;i<p->getEdges().size();i++){
            if(p->getEdges().getValueAt(i)->getEndNode()->getKey()==u->getKey()){
                
                tmp.append(p->getEdges().getValueAt(i));
            }
        }
        u=p;
    }
    delete[] dist;
    delete[] prev;

    return tmp;

}

void DiGraph::setVisualizer(GraphVisualizer *graphviz){
    this->graphviz = graphviz;
}
GraphVisualizer *DiGraph::getVisualizer(){
    return this->graphviz;
}