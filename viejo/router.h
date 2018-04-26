#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <string>
#include <vector>

class Router
{
public:
    router();
    router(std::string name);
    std::string nameNode;
    std::vector <router> nodeList;
    std::vector <int> costList;
    void addNode(router router , int cost);

};

#endif // ROUTER_H
