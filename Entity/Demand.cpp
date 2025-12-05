#include "Demand.h"
#include <iostream>
#include <fstream>

Demand::Demand() {
    this->departure = std::string();
    this->destination = std::string();
}

bool Demand::initialDemand(const std::string &demand) {
    std::ifstream demandFile(demand);
    if (!demandFile.is_open()) {
        std::cout << demand << "无法打开" << std::endl;
        return false;
    }

    std::string startLine;
    std::string endLine;
    std::getline(demandFile, startLine);
    std::getline(demandFile, endLine);
    this->departure = startLine.substr(startLine.find("：") + 3);
    this->destination = endLine.substr(endLine.find("：") + 3);
    return true;
}

std::string Demand::getDeparture() const {
    return this->departure;
}

std::string Demand::getDestination() const {
    return this->destination;
}
