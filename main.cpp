#include <iostream>
#include "graph.h"

int main()
{

    Graph net("NETWORK");

    /*Put graph files in the respective directory*/

    /*Load File Demo*/
    net.loadEdgeFile("netA.txt");
    net.printGraphNodes();
    net.printGraphEdges();
    net.showAllNodeTables();
    net.showTableOfGraph();
    net.deleteGraph();

    /*Change graph topology on execution time*/
    net.loadEdgeFile("netB.txt");
    net.printGraphNodes();
    net.printGraphEdges();
    net.showAllNodeTables();
    net.showTableOfGraph();
    net.deleteGraph();


    /*Random Graph Demo*/
    Graph netr("RANDOM NETWORK");
    netr.generateRandomGraph(4,8,1,7);
    netr.printGraphNodes();
    netr.printGraphEdges();
    netr.showAllNodeTables();
    netr.showTableOfGraph();

    /*Save Random Graph to File*/
    netr.saveGraphToFile("randNet.txt");
    netr.deleteGraph();
    return 0;
}
