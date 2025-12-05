#ifndef DS_PJ_ROAD_H
#define DS_PJ_ROAD_H

#include <string>

class Road {
public:
    Road();

    void initialRoad(const std::string &startPoint, const std::string &endPoint, double length, double speedLimit,
                     double lanes, double cars);

    [[nodiscard]] std::string getStartPoint() const;

    [[nodiscard]] std::string getEndPoint() const;

    [[nodiscard]] double getIndex() const;

private:
    std::string startPoint;
    std::string endPoint;
    double length;
    double speedLimit;
    double lanes;
    double cars;
    double index;
};

#endif //DS_PJ_ROAD_H
