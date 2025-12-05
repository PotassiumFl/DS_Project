#ifndef DS_PJ_GRAPH_H
#define DS_PJ_GRAPH_H


#include <vector>
#include <map>
#include <string>

class Graph {
public:
    Graph();

    void printDistanceMatrix() const;

    void printGraph() const;

    std::vector<std::string> findRoute(const std::string &start, const std::string &end);

    [[nodiscard]] std::vector<std::string> findRoute(int start, int end) const;

    bool ifConnected(const std::string &start, const std::string &end);

    [[nodiscard]] bool ifConnected(int start, int end) const;

    bool neighbors(const std::string &vertice);

    [[nodiscard]] bool neighbors(int vertice) const;

    bool insertVertice(const std::string &vertice);

    bool deleteVertice(const std::string &vertice);

    bool deleteVertice(int vertice);

    bool addEdge(const std::string &start, const std::string &end, double weight);

    bool addEdge(int start, int end, double weight);

    bool deleteEdge(const std::string &start, const std::string &end);

    bool deleteEdge(int start, int end);

    bool clearEdge();

    int firstNeighbor(const std::string &vertice);

    [[nodiscard]] int firstNeighbor(int vertice) const;

    int nextNeighbor(const std::string &vertice, const std::string &from);

    [[nodiscard]] int nextNeighbor(int vertice, int from) const;

    double getEdgeWeight(const std::string &start, const std::string &end);

    [[nodiscard]] double getEdgeWeight(int start, int end) const;

    bool setEdgeWeight(const std::string &start, const std::string &end, double weight);

    bool setEdgeWeight(int start, int end, double weight);

private:
    std::map<std::string, int> verticeToInt;
    std::vector<std::string> verticeList;
    std::vector<std::vector<double> > distanceMatrix;
};


#endif //DS_PJ_GRAPH_H