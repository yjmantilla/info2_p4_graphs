#include "router.h"
#include <string>

router::router()
{

}


router::router(std::string name)
{
    this->nameNode = name;
    std::cout<<"\nrouter created\n";
}

void router::addNode(router router, int cost)
{

}

