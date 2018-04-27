#include <iostream>
#include "graph.h"

int main()
{
    Node A("A");
    Node B("B");
    Node C("C");
    Node D("D");

    Edge eAB("1",4,A,B);
    Edge eBD("2",1,B,D);
    Edge eDC("3",2,D,C);
    Edge eAC("4",10,A,C);

    Graph network("Network 1");

    network.graphNodes.push_back(A);
    network.graphNodes.push_back(B);
    network.graphNodes.push_back(C);
    network.graphNodes.push_back(D);

    network.graphEdges.push_back(eAB);
    network.graphEdges.push_back(eBD);
    network.graphEdges.push_back(eDC);
    network.graphEdges.push_back(eAC);

    network.printGraphNodes();
    network.printGraphEdges();
    network.buildTable(&A);
    return 0;
}
