#ifndef DS_PJ_DEMAND_H
#define DS_PJ_DEMAND_H

#include <string>

class Demand {
public:
    Demand();

    bool initialDemand(const std::string &demand);

    [[nodiscard]] std::string getDeparture() const;

    [[nodiscard]] std::string getDestination() const;

private:
    std::string departure;

    std::string destination;
};

#endif //DS_PJ_DEMAND_H
