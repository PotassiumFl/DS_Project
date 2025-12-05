#ifndef DS_PJ_MAP_H
#define DS_PJ_MAP_H

#include "Demand.h"
#include "Graph.h"
#include <vector>


class Map {
public:
    Map();

    bool initialMap(const std::string &mapFile, const std::string &demandFile);

    bool updateMap(const std::string &mapFile);

    bool findRoute();

    void printRoute() const;

private:
    Graph graph;
    Demand demand;
    std::vector<std::string> route;
};



#endif //DS_PJ_MAP_H