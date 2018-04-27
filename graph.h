#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>

class Node
{
public:

//properties
std::string name;


//routing table
std::vector <Node> visitedNodes;
std::vector <Node> unvisitedNodes;
std::vector <Node> connectedNodes;
std::vector <int> connectedWeights;
std::vector <Node> prevNode;
std::vector <int> shortestPath;

//methods
    Node();
    Node(std::string name);
    std::string getNodeName();
    bool compareToNode(Node b);


};

class Edge
{
public:
    //properties
    std::string name;
    int weight;
    std::vector<Node> link;

    //methods
    Edge();
    Edge(std::string name, int weight, Node a, Node b);
    int getEdgeWeight();
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
    Graph(std::string name);
    void printGraphNodes();
    void printGraphEdges();
    void buildTable(Node * node);
};

#endif // GRAPH_H
