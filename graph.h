#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <stack>

/*
For best formating use nodes and weights of single characters.
*/

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
    Edge(int weight, Node a, Node b);
    Edge(std::string name);
    int getEdgeWeight();
    Node getNodeA();
    Node getNodeB();
    void printEdge();
    std::string getEdgeName();
    bool compareToEdge(Edge b);

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
    std::string getGraphName();
    void printGraphNodes();
    void printGraphEdges();
    int buildTable(Node * node);
    int buildTable(std::string nodeName);
    std::string getTheWay(Node * start, Node * end);
    std::string getTheWay(std::string start, std::string end);
    int getWayWeight(Node * start, Node * end);
    int getWayWeight(std::string start, std::string end);
    bool findNode(Node whatToFind, std::vector<Node> whereToFindIt, unsigned int * position);
    bool findNode(Node whatToFind, std::vector<Node> whereToFindIt);
    bool findEdge(Edge whatToFind, std::vector<Edge> whereToFindIt);
    bool findEdge(Edge whatToFind, std::vector<Edge> whereToFindIt, unsigned int * position);
    void addNode(Node a);
    void addNode(std::string name);
    void addEdge(Edge a);
    void addEdge(std::string name, int weight, std::string nameA, std::string nameB);
    void addEdge(std::string name, int weight, Node A, Node B);
    void addEdge(int weight, std::string nameA, std::string nameB);
    void addEdge(int weight, Node A, Node B);
    void addNodesFromEdge(Edge e);
    void addNodesFromGraphEdges();
    void deleteNode(Node a);
    void deleteNode(std::string nameA);
    void deleteEdge(Edge a);
    void deleteEdge(std::string nameE);
    void deleteEdge(int weight, Node A, Node B);
    void deleteEdge(int weight, std::string nameA, std::string nameB);
    void showTableOfNode(Node a);
    void showTableOfNode(std::string nameA);
    void showTableOfGraph();
    void showAllNodeTables();
    void loadEdgeFile(std::string filename);
    void deleteGraph();
    void generateRandomGraph(unsigned int numberOfNodes, unsigned int numberOfEdges, unsigned int minWeight, unsigned int maxWeight);
    void saveGraphToFile(std::string filename);

};

#endif // GRAPH_H
