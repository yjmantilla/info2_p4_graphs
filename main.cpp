#include <iostream>
#include "graph.h"

int main()
{

    Graph network("Network 1");

    network.addNode("A");
    network.addNode("B");
    network.addNode("C");
    network.addNode("D");
    network.addEdge("AB",4,"A","B");
    network.addEdge("BD",1,"B","D");
    network.addEdge("DC",2,"D","C");
    network.addEdge("CA",10,"C","A");

    Graph network2("Network 2");

    network2.addEdge(7,"A","B");
    network2.addEdge(3,"A","C");
    network2.addEdge(1,"C","B");
    network2.addEdge(2,"C","D");
    network2.addEdge(2,"B","D");
    network2.addEdge(4,"D","E");
    network2.addEdge(6,"B","E");
    network2.addNodesFromGraphEdges();

    network.addNode("A");
    network.addEdge(4,"B","A");
    network.printGraphNodes();
    network.printGraphEdges();
    std::cout<<std::endl;
    network2.printGraphNodes();
    network2.printGraphEdges();
    std::cout<<std::endl;
    network.buildTable("A");
    std::cout<<network.getTheWay("A","C")<<" with cost "<<network.getWayWeight("A","C");

    std::cout<<std::endl;

    network2.buildTable("A");
    std::cout<<network2.getTheWay("A","E")<<" with cost "<<network2.getWayWeight("A","E");
    std::cout<<std::endl;
    return 0;
}
