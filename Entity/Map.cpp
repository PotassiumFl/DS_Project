#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Road.h"


Map::Map() {
    this->graph = Graph();
    this->demand = Demand();
    this->route = std::vector<std::string>();
}

bool Map::initialMap(const std::string &mapFile, const std::string &demandFile) {
    std::ifstream file(mapFile);
    std::string line;
    Road roadTmp;
    std::vector<Road> roads;
    std::map<std::string, int> columnIndex;

    if (!file.is_open()) {
        std::cout << mapFile << "无法打开" << std::endl;
        return false;
    }

    ///列引索处理
    std::getline(file, line);
    std::stringstream ss(line);
    std::string item;
    while (getline(ss, item, ',')) {
        columnIndex[item] = static_cast<int>(columnIndex.size());
    }

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        ss = std::stringstream(line);

        while (getline(ss, item, ',')) {
            row.push_back(item);
        }

        std::string start = row[columnIndex["起始地点"]];
        std::string end = row[columnIndex["目标地点"]];
        std::string direction = row[columnIndex["道路方向"]];
        double length = std::stod(row[columnIndex["道路长度(米)"]]);
        double speedLimit = std::stod(row[columnIndex["道路限速(km/h)"]]);
        double lanes = std::stod(row[columnIndex["车道数"]]);
        double cars = std::stod(row[columnIndex["现有车辆数"]]);
        roadTmp.initialRoad(start, end, length, speedLimit, lanes, cars);
        roads.emplace_back(roadTmp);
        if (direction == "双向") {
            roadTmp.initialRoad(end, start, length, speedLimit, lanes, cars);
            roads.emplace_back(roadTmp);
        }
        graph.insertVertice(start);
        graph.insertVertice(end);
    }
    for (const auto &road : roads) {
        this->graph.setEdgeWeight(road.getStartPoint(),road.getEndPoint(),road.getIndex());
    }

    return this->demand.initialDemand(demandFile);
}

bool Map::updateMap(const std::string &mapFile) {
    std::ifstream file(mapFile);
    std::string line;
    Road roadTmp;
    std::vector<Road> roads;
    std::map<std::string, int> columnIndex;

    if (!file.is_open()) {
        std::cout << mapFile << "无法打开" << std::endl;
        return false;
    }

    std::getline(file, line);
    std::stringstream ss(line);
    std::string item;
    while (getline(ss, item, ',')) {
        columnIndex[item] = static_cast<int>(columnIndex.size());
    }

    while (std::getline(file, line)) {
        std::vector<std::string> row;
        ss = std::stringstream(line);

        while (getline(ss, item, ',')) {
            row.push_back(item);
        }

        std::string start = row[columnIndex["起始地点"]];
        std::string end = row[columnIndex["目标地点"]];
        std::string direction = row[columnIndex["道路方向"]];
        double length = std::stod(row[columnIndex["道路长度(米)"]]);
        double speedLimit = std::stod(row[columnIndex["道路限速(km/h)"]]);
        double lanes = std::stod(row[columnIndex["车道数"]]);
        double cars = std::stod(row[columnIndex["现有车辆数"]]);

        roadTmp.initialRoad(start, end, length, speedLimit, lanes, cars);
        roads.emplace_back(roadTmp);
        if (direction == "双向") {
            roadTmp.initialRoad(end, start, length, speedLimit, lanes, cars);
            roads.emplace_back(roadTmp);
        }
    }
    this->graph.clearEdge();
    for (const auto &road : roads) {
        this->graph.setEdgeWeight(road.getStartPoint(),road.getEndPoint(),road.getIndex());
    }
    return true;
}

bool Map::findRoute() {
    this->route=this->graph.findRoute(this->demand.getDeparture(),this->demand.getDestination());
    return true;
}

void Map::printRoute() const {
    std::cout << route[0];
    for (int i=1;i<route.size();i++) {
        std::cout << "-->" << route[i];
    }
    std::cout << std::endl;
}
