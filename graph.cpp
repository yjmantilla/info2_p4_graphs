#include "graph.h"
#include <algorithm>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>

#define MAX_INT 32767 // represents infinite weigth (node is unreachable)

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
    //std::cout<<this->getNodeName()<<" "<<b.getNodeName()<<" "<<!this->getNodeName().compare(b.getNodeName())<<"\n";
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

Edge::Edge(int weight, Node a, Node b)
{
    this->weight = weight;
    this->link.push_back(a);
    this->link.push_back(b);
}

Edge::Edge(std::string name)
{
    this->name = name;
}

int Edge::getEdgeWeight()
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
    std::cout<<this->link.front().getNodeName()<<"-"<<this->getEdgeWeight()<<"-"<<this->link.back().getNodeName()<<"\n";
}

std::string Edge::getEdgeName()
{
    return this->name;
}

bool Edge::compareToEdge(Edge b)
{
    if(this->getEdgeName().empty()&&b.getEdgeName().empty())
    {}
    else
    {
        if(this->getEdgeName().compare(b.getEdgeName())==0){return true;}
    }

    if(this->getNodeA().compareToNode(b.getNodeA())&&this->getNodeB().compareToNode(b.getNodeB())&&this->getEdgeWeight()==b.getEdgeWeight())
    {
        return true;
    }

    if(this->getNodeA().compareToNode(b.getNodeB())&&this->getNodeB().compareToNode(b.getNodeA())&&this->getEdgeWeight()==b.getEdgeWeight())
    {
        return true;
    }

    return false;
}




Graph::Graph()
{

}

Graph::Graph(std::string name)
{
    this->name=name;
}

std::string Graph::getGraphName()
{
 return this->name;
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

int Graph::buildTable(Node * node)
{
    /*
     *  Based on:https://medium.com/basecs/finding-the-shortest-path-with-a-little-help-from-dijkstra-613149fbdc8e
     *  Dijkstra’s algorithm can be used to determine the shortest path from one node
     *  in a graph to every other node within the same graph data structure, provided
     *  that the nodes are reachable from the starting node.
    */
    //check if node exist on graph
    if(!this->findNode(*node,this->graphNodes))
    {
        std::cout<<"\nNode not found, breaking operation...\n";
        return -1;
    }

    //initialization of the algorithm
    node->unvisitedNodes = this->graphNodes;
    node->shortestPath.resize(this->graphNodes.size());
    node->prevNode.resize(this->graphNodes.size());


    // give infinite weight to all nodes except the node which is the same as the starting node
    for(unsigned int i=0;i<this->graphNodes.size();i++)
    {
        if(node->compareToNode(this->graphNodes[i])){node->shortestPath[i]=0;}
        else{node->shortestPath[i]=MAX_INT;}
    }

    //start of the table building loop, while we have not visited all the nodes
    while(node->visitedNodes.size()<this->graphNodes.size())
    {
        //determine the node with smallest known weight that also we have not visited yet

        unsigned int smallest=0;//we start supposing smallest is at position zero
        //we are gonna move our smallest supposition until we find one that has not been visited
        bool smallestAlreadyVisited;
        while(1)
        {
        smallestAlreadyVisited = Graph::findNode(this->graphNodes[smallest],node->visitedNodes);
        if(smallestAlreadyVisited){smallest++;}
        else{break;}
        }

        //all we have until now is a supposition of a smallest node that is unvisited

        //scan through shortestPath vector for smaller nodes which has not been visited
        bool wasItVisited;

        for(unsigned int i = 0; i < node->shortestPath.size(); i++)
        {
            //see if current node of the iteration has been visited
            wasItVisited = Graph::findNode(this->graphNodes[i],node->visitedNodes);
            //we visit the node if it is the smallest of the nodes which have not been visited

            if(node->shortestPath[i] < node->shortestPath[smallest] && !wasItVisited)
            {
                //for debug
                //std::cout<<"\n"<<node->shortestPath[i]<<" < "<<node->shortestPath[smallest]<<"\n";

                smallest = i;//if it is smaller than our unvisited supposition we update our supposition
            }
        }

        //at this point smallest holds the index of the smallest node that is unvisited

        //for debug
        //std::cout<<"\nNode with smallest weight: " <<smallest /*- node->shortestPath.begin()*/<<"\n";
        //std::cout<<"\nWhich is node: "<<this->graphNodes[smallest].getNodeName()<<"\n";

        //find connected nodes of smallest and put them in connectedNodes
        //we scan the edges looking for one which has smallest node in it, either in position A or B
        for(unsigned int i=0;i<this->graphEdges.size();i++)
        {
            //if we find it in A then the connected node is in B and viceversa
            if(graphEdges[i].getNodeA().compareToNode(this->graphNodes[smallest]))
            {
            //std::cout<<"linkA \n"; //for the debug
            node->connectedNodes.push_back(graphEdges[i].getNodeB());
            node->connectedWeights.push_back(graphEdges[i].getEdgeWeight());
            }

            if(graphEdges[i].getNodeB().compareToNode(this->graphNodes[smallest]))
            {
             //std::cout<<"linkB \n"; //for the debug
             node->connectedNodes.push_back(graphEdges[i].getNodeA());
             node->connectedWeights.push_back(graphEdges[i].getEdgeWeight());
            }
        }

        //start visiting the connected nodes
        for(unsigned int i=0;i<node->connectedNodes.size();i++)
        {
            //we sum the weight of the smallest node to the weight of the current connection being evaluated
            node->connectedWeights[i]= node->shortestPath[smallest]+node->connectedWeights[i];
            //std::cout<<"\n"<<node->connectedWeights[i]<<"\n"; //for debug

            //update shortestPath table if we find a shorter connection
            //scan through shortestPath vector and see if the current connection is shorter than the respective there
            for(unsigned int j=0;j<this->graphNodes.size();j++)
            {
                //exp says if the connection is shorter
                //bool exp = node->connectedWeights[i] < node->shortestPath[j];
                //std::cout<<"\nca:"<<exp<<"\ncb: "<<node->connectedNodes[i].compareToNode(this->graphNodes[j])<<"\n"; //for debug

                //we need shorter and also that it holds the same connection
                if(node->connectedWeights[i] < node->shortestPath[j] && node->connectedNodes[i].compareToNode(this->graphNodes[j]) )
                {
                    node->shortestPath[j] = node->connectedWeights[i];
                    node->prevNode[j] = this->graphNodes[smallest];
                    //std::cout<<"\nConnected to "<<node->connectedNodes[i].getNodeName()<<" with weight "<<node->shortestPath[j]<<" came from "<<this->graphNodes[s].getNodeName()<<"\n"; //for debug
                }
            }

        }

        //smallest node is visited now, we add it to visited and delete it from unvisited
        node->visitedNodes.push_back(this->graphNodes[smallest]);
        node->unvisitedNodes.erase(node->unvisitedNodes.begin()+smallest);
    }

    //print results for debug
//    std::cout<<"\n\n\n";
//    for(unsigned int i = 0;i<this->graphNodes.size();i++)
//    {
//        std::cout<<this->graphNodes[i].getNodeName()<<" "<<node->shortestPath[i]<<" "<<node->prevNode[i].getNodeName()<<"\n";
//    }

    //clean vectors for further updating
    node->visitedNodes.erase(node->visitedNodes.begin(),node->visitedNodes.end());
    node->unvisitedNodes.erase(node->unvisitedNodes.begin(),node->unvisitedNodes.end());
    node->connectedNodes.erase(node->connectedNodes.begin(),node->connectedNodes.end());
    node->connectedWeights.erase(node->connectedWeights.begin(),node->connectedWeights.end());

    //flat the info of previous nodes, increase of performance
    for(unsigned int i = 0; i < this->graphNodes.size();i++)
    {
        node->prevNode[i].prevNode.erase(node->prevNode[i].prevNode.begin(),node->prevNode[i].prevNode.end());
        node->prevNode[i].shortestPath.erase(node->prevNode[i].shortestPath.begin(),node->prevNode[i].shortestPath.end());
        node->prevNode[i].unvisitedNodes.erase(node->prevNode[i].unvisitedNodes.begin(),node->prevNode[i].unvisitedNodes.end());
        node->prevNode[i].visitedNodes.erase(node->prevNode[i].visitedNodes.begin(),node->prevNode[i].visitedNodes.end());
        node->prevNode[i].connectedNodes.erase(node->prevNode[i].connectedNodes.begin(),node->prevNode[i].connectedNodes.end());
        node->prevNode[i].connectedWeights.erase(node->prevNode[i].connectedWeights.begin(),node->prevNode[i].connectedWeights.end());
    }
    return 0;
}

int Graph::buildTable(std::string nodeName)
{
    Node dummy(nodeName);
    if (buildTable(&dummy) == -1) {return -1;}
    else{return 0;}
}

std::string Graph::getTheWay(Node * start, Node * end)
{
 std::string wayString;
 std::stack<Node> way;

 //update routing table of start node.
 this->buildTable(start);

 //find position of end node, it was not necessary? but verify it exist
 unsigned int position;

 if (!Graph::findNode(*end,this->graphNodes,&position)){return "unreachable";}

 way.push(*end);

 while(!start->compareToNode(way.top()))
 {
   Graph::findNode(way.top(),this->graphNodes,&position);
   way.push(start->prevNode.at(position));
 }

 while(!way.empty())
 {
     wayString.append(way.top().getNodeName());
     way.pop();
     if(!way.empty()){wayString.append("-");}
 }

 //std::cout<<"\n"<<wayString<<"\n";//nice crash dud
 return wayString;
}

std::string Graph::getTheWay(std::string start, std::string end)
{
    Node dummys(start);
    Node dummye(end);

    std::string way;
    way = this->getTheWay(&dummys,&dummye);
    return way;
}

int Graph::getWayWeight(Node *start, Node *end)
{
    //update routing table of start node.
    this->buildTable(start);

    //find position of end node, it was not necessary? but verify it exist
    unsigned int position;

    if (!Graph::findNode(*end,this->graphNodes,&position)){std::cout<<"\nWarning node is unreachable, returning max integer possible...\n";return MAX_INT; /*unreachable*/}

    return start->shortestPath.at(position);

}

int Graph::getWayWeight(std::string start, std::string end)
{
    Node dummys(start);
    Node dummye(end);

    return this->getWayWeight(&dummys,&dummye);
}

bool Graph::findNode(Node whatToFind, std::vector<Node> whereToFindIt, unsigned int *position)
{
    for(unsigned int j=0; j<whereToFindIt.size();j++)
    {
        if(whereToFindIt.at(j).compareToNode(whatToFind))
        {
            *position=j;
            return true;
        }
    }

    position = NULL;
    return false;
}

bool Graph::findNode(Node whatToFind, std::vector<Node> whereToFindIt)
{
    for(unsigned int j=0; j<whereToFindIt.size();j++)
    {
        if(whereToFindIt.at(j).compareToNode(whatToFind))
        {
            return true;
        }
    }

    return false;
}

bool Graph::findEdge(Edge whatToFind, std::vector<Edge> whereToFindIt)
{
    for(unsigned int j=0; j<whereToFindIt.size();j++)
    {
        if(whereToFindIt.at(j).compareToEdge(whatToFind))
        {
            return true;
        }
    }

    return false;
}

bool Graph::findEdge(Edge whatToFind, std::vector<Edge> whereToFindIt, unsigned int *position)
{

    for(unsigned int j=0; j<whereToFindIt.size();j++)
    {
        if(whereToFindIt.at(j).compareToEdge(whatToFind))
        {
            *position = j;
            return true;
        }
    }

    position = NULL;
    return false;
}


void Graph::addNode(Node a)
{
    if(this->findNode(a,this->graphNodes)){std::cout<<"\nError. Node "<<a.getNodeName()<<" already exist...\n";return;}
    this->graphNodes.push_back(a);
}

void Graph::addNode(std::string name)
{
    Node dummy(name);
    this->addNode(dummy);
}

void Graph::addEdge(Edge a)
{
    if(this->findEdge(a,this->graphEdges)){std::cout<<"\nError. Edge "<<a.getEdgeName()<<" already exist...\n";return;}
    this->graphEdges.push_back(a);
}

void Graph::addEdge(std::string name, int weight, std::string nameA, std::string nameB)
{
    Node dummyA(nameA);
    Node dummyB(nameB);
    Edge dummy(name,weight,dummyA,dummyB);
    this->addEdge(dummy);
}

void Graph::addEdge(std::string name, int weight, Node A, Node B)
{
    Edge dummy(name,weight,A,B);
    this->addEdge(dummy);
}

void Graph::addEdge(int weight, std::string nameA, std::string nameB)
{
    Node dummyA(nameA);
    Node dummyB(nameB);
    Edge dummy(weight,dummyA,dummyB);
    this->addEdge(dummy);
}

void Graph::addEdge(int weight, Node A, Node B)
{
    Edge dummy(weight,A,B);
    this->addEdge(dummy);
}

void Graph::addNodesFromEdge(Edge e)
{
    this->addNode(e.getNodeA());
    this->addNode(e.getNodeB());
    return;
}

void Graph::addNodesFromGraphEdges()
{
    for(unsigned int i = 0;i < this->graphEdges.size();i++)
    {
        this->addNodesFromEdge(graphEdges.at(i));
    }

    return;
}

void Graph::deleteNode(Node a)
{
    unsigned int pos;
    if(!this->findNode(a,this->graphNodes,&pos))
    {
        std::cout<<"\nError, Node "<<a.getNodeName()<<" does not exist...\n";
        return;
    }

    else
    {
        this->graphNodes.erase(this->graphNodes.begin() + pos);

        //delete edges related to node
        for(unsigned int j=0; j<this->graphEdges.size();j++)
        {
            if(this->graphEdges.at(j).getNodeA().compareToNode(a)||this->graphEdges.at(j).getNodeB().compareToNode(a))
            {
                this->graphEdges.erase(this->graphEdges.begin() + j);
            }
        }

    }

    std::cout<<"\nNode "<<a.getNodeName()<<" and associated Edges deleted\n";
    return;
}

void Graph::deleteNode(std::string nameA)
{
    Node a(nameA);
    this->deleteNode(a);
    return;
}

void Graph::deleteEdge(Edge a)
{
    unsigned int pos;
    if (!this->findEdge(a,this->graphEdges,&pos))
    {
        std::cout<<"\nError, Edge "<<a.getEdgeName()<<" does not exist...\n";
    }
    else
    {
        this->graphEdges.erase(this->graphEdges.begin() + pos);
    }
    std::cout<<"\nEdge "<<a.getEdgeName()<<" deleted\n";
    return;
}

void Graph::deleteEdge(std::string nameE)
{
    Edge E(nameE);

    this->deleteEdge(E);
    return;
}

void Graph::deleteEdge(int weight, Node A, Node B)
{
    Edge E(weight,A,B);
    this->deleteEdge(E);
    return;
}

void Graph::deleteEdge(int weight, std::string nameA, std::string nameB)
{
    Node A(nameA);
    Node B(nameB);

    this->deleteEdge(weight,A,B);
    return;
}

void Graph::showTableOfNode(Node a)
{
    //update table

    this->buildTable(&a);

    //print results for debug
    std::cout<<"\nNode "<<a.getNodeName()<<" table of Graph "<<this->getGraphName()<<":\n";

    std::cout<<"\nName SP Way\n";

    for(unsigned int i = 0;i<this->graphNodes.size();i++)
    {
        std::cout<<this->graphNodes[i].getNodeName()<<"    "<<a.shortestPath[i]<<"  "<<this->getTheWay(a.getNodeName(),this->graphNodes.at(i).getNodeName())<<"\n";
    }

    std::cout<<std::endl;
    return;
}

void Graph::showTableOfNode(std::string nameA)
{
    Node A(nameA);

    this->showTableOfNode(A);
    return;
}

void Graph::showTableOfGraph() //for some reason this code makes the program slow
{
    std::cout<<"\nTable of Graph: "<<this->getGraphName()<<"\n\n  ";
    for(unsigned int i = 0; i < this->graphNodes.size(); i++)
    {
        std::cout<<this->graphNodes.at(i).getNodeName()<<" ";
    }

    std::cout<<"\n";

    for(unsigned int i = 0; i < this->graphNodes.size(); i++)
    {
        this->buildTable(&this->graphNodes.at(i));
        std::cout<<this->graphNodes.at(i).getNodeName()<<" ";
        for(unsigned int j = 0; j < this->graphNodes.size(); j++)
        {
            std::cout<<this->graphNodes.at(i).shortestPath.at(j)<<" ";
        }

        std::cout<<std::endl;
    }

    return;
}

void Graph::showAllNodeTables()
{
    for(unsigned int i =0;i < this->graphNodes.size();i++)
    {
        this->showTableOfNode(this->graphNodes.at(i));
    }

    return;
}

void Graph::loadEdgeFile(std::string filename)
{
    std::fstream ifs(filename,std::ifstream::in);
    if(!ifs.good()){std::cout<<"\nError opening file\n";return;}

    std::string buffer;
    std::string nodeA;
    std::string nodeB;
    std::string weight_s;
    int weight;

    std::cout<<"\nLoading Edges from "<<filename<<":\n";
    while(1)
    {
        std::getline(ifs,buffer);

        //if(!ifs.good()){break;}

        //check if buffer is empty (there is empty line), jump to next line
        if(buffer.empty()){continue;}

        unsigned int i = 0;
        while(1)
        {
            if(buffer.at(i)==','){i++;break;}
            nodeA.push_back(buffer.at(i));
            i++;
        }

        while(1)
        {
            if(buffer.at(i)==','){i++;break;}
            weight_s.push_back(buffer.at(i));
            i++;
        }

        while(1)
        {
            if(i==buffer.length()){break;}
            nodeB.push_back(buffer.at(i));
            i++;
        }

        weight = std::stoi(weight_s);
        std::cout<<nodeA<<"-"<<weight<<"-"<<nodeB<<"\n";
        this->addEdge(weight,nodeA,nodeB);

        nodeA.erase(nodeA.begin(),nodeA.end());
        nodeB.erase(nodeB.begin(),nodeB.end());
        weight_s.erase(weight_s.begin(),weight_s.end());
        if(!ifs.good()){break;}

    }

    ifs.close();

    this->addNodesFromGraphEdges();
    return;
}

void Graph::deleteGraph()
{
    this->graphEdges.erase(this->graphEdges.begin(),this->graphEdges.end());
    this->graphNodes.erase(this->graphNodes.begin(),this->graphNodes.end());
    return;
}

void Graph::generateRandomGraph(unsigned int numberOfNodes,unsigned int numberOfEdges,unsigned int minWeight, unsigned int maxWeight)
{
    /*
     * Recommended that number of nodes is less than 25 (A to Z)
     * Edges are recommended to be equal or more than number of nodes but is not necessary
     * Weights should be higher than 0 and less than MAX_INT (32767)
     * Consider weights below 7 so that the paths are single digit, in that case the
     * formatting of tables is neat.
     * Eventually it could generate Graph that are not closed , in that case it hangs...
     * This is because of the nature of the Dijkstra's Algorithm. It needs reachable nodes.
     * To avoid that consider putting considerable more edges than nodes
    */

    srand (time(NULL));

    while(this->graphEdges.size()<numberOfEdges)
    {
        char a = 'A';
        char b = 'A';

        //avoid self connecting nodes
        while(a==b)
        {

            a = rand() % ('A'+ numberOfNodes - 'A' + 1) + 'A';
            b = rand() % ('A'+ numberOfNodes - 'A' + 1) + 'A';
        }

        // std::cout<<"\n"<<a<<"-"<<b<<"\n";
        std::string sa;
        std::string sb;

        sa.push_back(a);
        sb.push_back(b);

        int weight = rand() % (maxWeight - minWeight + 1) + minWeight;

        this->addEdge(weight,sa,sb);
    }

    this->addNodesFromGraphEdges();
}

void Graph::saveGraphToFile(std::string filename)
{
    std::fstream ofs(filename,std::ifstream::out| std::fstream::trunc);
    for(unsigned int i =0;i < this->graphEdges.size();i++)
    {
        if(i<this->graphEdges.size()-1)
        {
            ofs<<this->graphEdges.at(i).getNodeA().getNodeName()<<","<<this->graphEdges.at(i).getEdgeWeight()<<","<<this->graphEdges.at(i).getNodeB().getNodeName()<<"\n";
        }
        else //last
        {
            ofs<<this->graphEdges.at(i).getNodeA().getNodeName()<<","<<this->graphEdges.at(i).getEdgeWeight()<<","<<this->graphEdges.at(i).getNodeB().getNodeName();
        }
    }

    ofs.close();
}

