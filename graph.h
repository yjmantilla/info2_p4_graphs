#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>

class Node
{
public:

//properties
std::string name;


//methods
    Node();
    Node(std::string name);
    std::string getNodeName();

};

class Edge
{
public:
    //properties
    std::string name;
    float weight;
    std::vector<Node> link;

    //methods
    Edge();
    Edge(std::string name, float weight, Node a, Node b);
    float getEdgeWeight();
    Node getNodeA();
    Node getNodeB();
    void printEdge();

};

class Graph
{
public:
    //properties
    std::vector<Node> graphNodes;
    std::vector<Edge> graphEdges;
    std::string name;

    //methods
    Graph();
};

#endif // GRAPH
