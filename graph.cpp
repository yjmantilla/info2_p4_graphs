#include "graph.h"
#define MAX_INT 32767

Node::Node()
{

}

Node::Node(std::string name)
{
    this->name = name;
}

std::string Node::getNodeName()
{
    return this->name;
}

bool Node::compareToNode(Node b)
{
    std::cout<<this->getNodeName()<<" "<<b.getNodeName()<<" "<<this->getNodeName().compare(b.getNodeName())<<"\n";
    if(this->getNodeName().compare(b.getNodeName())==0){return true;}
    else {return false;}
}


Edge::Edge(std::string name, int weight, Node a, Node b)
{
    this->name = name;
    this->weight = weight;
    this->link.push_back(a);
    this->link.push_back(b);
}

float Edge::getEdgeWeight()
{
    return this->weight;
}

Node Edge::getNodeA()
{
    return this->link.front();
}

Node Edge::getNodeB()
{
    return this->link.back();
}

void Edge::printEdge()
{
    std::cout<<this->link.front().getNodeName()<<"--"<<this->getEdgeWeight()<<"--"<<this->link.back().getNodeName()<<"\n";
}




Graph::Graph()
{

}

Graph::Graph(std::string name)
{
 this->name=name;
}

void Graph::printGraphNodes()
{
    std::cout<<"\n"<<this->name<<" nodes:\n";
    for(unsigned int i=0;i<graphNodes.size();i++)
    {
        std::cout<<graphNodes[i].getNodeName()<<"\n";
    }
}

void Graph::printGraphEdges()
{
    std::cout<<"\n"<<this->name<<" edges:\n";
    for(unsigned int i=0;i<graphEdges.size();i++)
    {
        this->graphEdges[i].printEdge();
    }
}

void Graph::buildTable(Node * node)
{
    node->nodeList = this->graphNodes;
    node->unvisitedNodes = this->graphNodes;
    node->shortestPath.resize(this->graphNodes.size());

    for(unsigned int i=0;i<node->nodeList.size();i++)
    {
        if(node->compareToNode(node->nodeList[i])){node->shortestPath[i]=0;}
        else{node->shortestPath[i]=MAX_INT;}
    }



}
