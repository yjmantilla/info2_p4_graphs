#include "graph.h"
#include <algorithm>
#include <stack>
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
    std::cout<<this->getNodeName()<<" "<<b.getNodeName()<<" "<<!this->getNodeName().compare(b.getNodeName())<<"\n";
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
    //initialization of the algorithm
    node->unvisitedNodes = this->graphNodes;
    node->shortestPath.resize(this->graphNodes.size());
    node->prevNode.resize(this->graphNodes.size());

    for(unsigned int i=0;i<this->graphNodes.size();i++)
    {
        if(node->compareToNode(this->graphNodes[i])){node->shortestPath[i]=0;}
        else{node->shortestPath[i]=MAX_INT;}
    }

    while(node->visitedNodes.size()<this->graphNodes.size())
    {
        //determine the node with smallest known weight


        unsigned int smallest=0;
        for(unsigned int i = 0; i < node->shortestPath.size(); i++)
        {
            bool wasItVisited=false;

//            for(unsigned int j=0; j<node->visitedNodes.size();j++)
//            {
//                if(this->graphNodes[i].compareToNode(node->visitedNodes[j]))
//                {
//                    wasItVisited=true;
//                }
//            }

            //reimplementation with new function
            unsigned int dummypos;
            wasItVisited = Graph::findNode(this->graphNodes[i],node->visitedNodes,&dummypos);

            bool smallestAlreadyVisited;

            while(1)
            {
            smallestAlreadyVisited = Graph::findNode(this->graphNodes[smallest],node->visitedNodes,&dummypos);
            if(smallestAlreadyVisited){smallest++;}
            else{break;}
            }

//            for(unsigned int j=0; j<node->visitedNodes.size();j++)
//            {
//                if(this->graphNodes[smallest].compareToNode(node->visitedNodes[j]))
//                {
//                    smallest++;
//                }
//            }



            if(node->shortestPath[i] < node->shortestPath[smallest] && !wasItVisited)
            {
                std::cout<<"\n"<<node->shortestPath[i]<<" < "<<node->shortestPath[smallest]<<"\n";
                smallest = i;
            }
        }

        //auto smallest = std::min_element(node->shortestPath.begin(),node->shortestPath.end());
        std::cout<<"\nNode with smallest weight: " <<smallest /*- node->shortestPath.begin()*/<<"\n";
        int unsigned s = smallest; //- node->shortestPath.begin();
        //problem, we need that the node was also not visited previously
        std::cout<<"\nWhich is node: "<<this->graphNodes[s].getNodeName()<<"\n";

        //find connected nodes of smallest and put them in connectedNodes
        for(unsigned int i=0;i<this->graphEdges.size();i++)
        {
            if(graphEdges[i].getNodeA().compareToNode(this->graphNodes[s]))
            {
            std::cout<<"linkA \n";
            node->connectedNodes.push_back(graphEdges[i].getNodeB());//is the other node which we connect dud
            node->connectedWeights.push_back(graphEdges[i].getEdgeWeight());
            }

            if(graphEdges[i].getNodeB().compareToNode(this->graphNodes[s]))
            {
             std::cout<<"linkB \n";
             node->connectedNodes.push_back(graphEdges[i].getNodeA());
             node->connectedWeights.push_back(graphEdges[i].getEdgeWeight());
            }
        }

        //start visiting
        for(unsigned int i=0;i<node->connectedNodes.size();i++)
        {
            node->connectedWeights[i]= node->shortestPath[s]+node->connectedWeights[i];
            std::cout<<"\n"<<node->connectedWeights[i]<<"\n";

            for(unsigned int j=0;j<this->graphNodes.size();j++)
            {
                bool exp = node->connectedWeights[i] < node->shortestPath[j];
                std::cout<<"\nca:"<<exp<<"\ncb: "<<node->connectedNodes[i].compareToNode(this->graphNodes[j])<<"\n";
                if(node->connectedWeights[i] < node->shortestPath[j] && node->connectedNodes[i].compareToNode(this->graphNodes[j]) )
                {
                    node->shortestPath[j] = node->connectedWeights[i];
                    node->prevNode[j] = this->graphNodes[s];
                    std::cout<<"\nConnected to "<<node->connectedNodes[i].getNodeName()<<" with weight "<<node->shortestPath[j]<<" came from "<<this->graphNodes[s].getNodeName()<<"\n";
                }
            }

        }


        node->visitedNodes.push_back(this->graphNodes[s]);
        node->unvisitedNodes.erase(node->unvisitedNodes.begin()+s);


    }

    std::cout<<"\n\n\n";
    for(unsigned int i = 0;i<this->graphNodes.size();i++)
    {
        std::cout<<this->graphNodes[i].getNodeName()<<" "<<node->shortestPath[i]<<" "<<node->prevNode[i].getNodeName()<<"\n";
    }

    //clean vectors for further updating
    node->visitedNodes.erase(node->visitedNodes.begin(),node->visitedNodes.end());
    node->unvisitedNodes.erase(node->unvisitedNodes.begin(),node->unvisitedNodes.end());
}

std::string Graph::getTheWay(Node * start, Node * end)
{
 std::string wayString;
 std::stack<Node> way;

 //update routing table of start node.
 this->buildTable(start); //apparently does not work, update table before calling function

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

