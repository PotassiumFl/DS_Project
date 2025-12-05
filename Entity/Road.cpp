#include "Road.h"
#include <iostream>
#include <limits>
#include <ostream>

Road::Road() {
    this->startPoint = std::string();
    this->endPoint = std::string();
    this->length = 0.0;
    this->speedLimit = 0.0;
    this->lanes = 0.0;
    this->cars = 0.0;
    this->index = std::numeric_limits<double>::infinity();
}

void Road::initialRoad(const std::string &startPoint, const std::string &endPoint, const double length,
                        const double speedLimit, const double lanes, const double cars) {
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->length = length;
    this->speedLimit = speedLimit;
    this->lanes = lanes;
    this->cars = cars;
    this->index = length / speedLimit * cars / lanes;
}

std::string Road::getStartPoint() const {
    return this->startPoint;
}

std::string Road::getEndPoint() const {
    return this->endPoint;
}

double Road::getIndex() const {
    return this->index;
}
