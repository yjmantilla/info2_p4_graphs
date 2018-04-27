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
    Edge eCA("4",10,C,A);

    Graph network("Network 1");

    Node a("a");
    Node b("b");
    Node c("c");
    Node d("d");
    Node e("e");

    Edge Eab("1",7,a,b);
    Edge Eac("2",3,a,c);
    Edge Ecb("3",1,c,b);
    Edge Ecd("4",2,c,d);
    Edge Ebd("5",2,b,d);
    Edge Ede("6",4,d,e);
    Edge Ebe("7",6,b,e);

    Graph network2("Network 2");

    network.graphNodes.push_back(A);
    network.graphNodes.push_back(B);
    network.graphNodes.push_back(C);
    network.graphNodes.push_back(D);

    network.graphEdges.push_back(eAB);
    network.graphEdges.push_back(eBD);
    network.graphEdges.push_back(eDC);
    network.graphEdges.push_back(eCA);

    network.printGraphNodes();
    network.printGraphEdges();
    network.buildTable(&D);
    std::cout<<std::endl;

    network2.graphNodes.push_back(a);
    network2.graphNodes.push_back(b);
    network2.graphNodes.push_back(c);
    network2.graphNodes.push_back(d);
    network2.graphNodes.push_back(e);

    network2.graphEdges.push_back(Eab);
    network2.graphEdges.push_back(Eac);
    network2.graphEdges.push_back(Ecb);
    network2.graphEdges.push_back(Ecd);
    network2.graphEdges.push_back(Ebd);
    network2.graphEdges.push_back(Ede);
    network2.graphEdges.push_back(Ebe);

    //network2.buildTable(&a);

    return 0;
}
