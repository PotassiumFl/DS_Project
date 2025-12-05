#include "Graph.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <stack>

///全空构造方法。
Graph::Graph() {
    this->verticeToInt = std::map<std::string, int>();
    this->verticeList = std::vector<std::string>();
    this->distanceMatrix = std::vector<std::vector<double> >();
}

void Graph::printDistanceMatrix() const {
    for (const auto &indexes: this->distanceMatrix) {
        for (const double index: indexes) {
            std::cout << index << "\t";
        }
        std::cout << std::endl;
    }
}

void Graph::printGraph() const {
    for (const auto &vertice: this->verticeList) {
        std::cout << vertice << " ";
    }
    std::cout << std::endl;
    this->printDistanceMatrix();
}

std::vector<std::string> Graph::findRoute(const std::string &start, const std::string &end) {
    int now = verticeToInt[start];
    std::vector<double> routeDistance;
    std::vector<bool> determined;
    std::vector route(this->verticeList.size(), -1);
    routeDistance.resize(this->verticeList.size(), std::numeric_limits<double>::max());
    determined.resize(this->verticeList.size(), false);

    routeDistance[now] = 0;
    determined[now] = true;

    for (int i = 0; i < this->verticeList.size() - 1; i++) {
        for (int j = 0; j < this->verticeList.size(); j++) {
            if (!determined[j]) {
                if (const double newDist = routeDistance[now] + this->distanceMatrix[now][j];
                    newDist < routeDistance[j]) {
                    routeDistance[j] = newDist;
                    route[j] = now;
                }
            }
        }

        double minDist = std::numeric_limits<double>::infinity();
        int nextNode = -1;

        for (int k = 0; k < this->verticeList.size(); k++) {
            if (!determined[k] && routeDistance[k] < minDist) {
                minDist = routeDistance[k];
                nextNode = k;
            }
        }

        if (nextNode == -1) break;

        determined[nextNode] = true;
        now = nextNode;
    }
    std::stack<int> invRoute;
    now = this->verticeToInt[end];
    invRoute.push(this->verticeToInt[end]);
    while (route[now] != this->verticeToInt[start]) {
        invRoute.push(route[now]);
        now = route[now];
    }

    std::vector<std::string> verticeRoute;
    while (!invRoute.empty()) {
        verticeRoute.push_back(this->verticeList[invRoute.top()]);
        invRoute.pop();
    }
    return verticeRoute;
}

std::vector<std::string> Graph::findRoute(const int start, const int end) const {
    int now = start;
    std::vector<double> routeDistance;
    std::vector<bool> determined;
    std::vector route(this->verticeList.size(), -1);
    routeDistance.resize(this->verticeList.size(), std::numeric_limits<double>::max());
    determined.resize(this->verticeList.size(), false);

    routeDistance[now] = 0;
    determined[now] = true;

    for (int i = 0; i < this->verticeList.size() - 1; i++) {
        for (int j = 0; j < this->verticeList.size(); j++) {
            if (!determined[j]) {
                if (const double newDist = routeDistance[now] + this->distanceMatrix[now][j];
                    newDist < routeDistance[j]) {
                    routeDistance[j] = newDist;
                    route[j] = now;
                }
            }
        }

        double minDist = std::numeric_limits<double>::infinity();
        int nextNode = -1;

        for (int k = 0; k < this->verticeList.size(); k++) {
            if (!determined[k] && routeDistance[k] < minDist) {
                minDist = routeDistance[k];
                nextNode = k;
            }
        }

        if (nextNode == -1) break;

        determined[nextNode] = true;
        now = nextNode;
    }

    std::stack<int> invRoute;
    now = end;
    invRoute.push(end);
    while (route[now] != start) {
        invRoute.push(route[now]);
        now = route[now];
    }

    std::vector<std::string> verticeRoute;
    while (!invRoute.empty()) {
        verticeRoute.push_back(this->verticeList[invRoute.top()]);
        invRoute.pop();
    }
    return verticeRoute;
}

bool Graph::ifConnected(const std::string &start, const std::string &end) {
    if (this->verticeToInt.find(start) == this->verticeToInt.end()) {
        std::cout << "节点" + start + "不存在" << std::endl;
        return false;
    }
    if (this->verticeToInt.find(end) == this->verticeToInt.end()) {
        std::cout << "节点" + end + "不存在" << std::endl;
        return false;
    }
    return this->distanceMatrix[this->verticeToInt[start]][this->verticeToInt[end]] == std::numeric_limits<
               double>::infinity();
}

bool Graph::ifConnected(const int start, const int end) const {
    if (start >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(start) + "不存在" << std::endl;
        return false;
    }
    if (end >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(end) + "不存在" << std::endl;
        return false;
    }
    return this->distanceMatrix[start][end] == std::numeric_limits<double>::infinity();
}

bool Graph::neighbors(const std::string &vertice) {
    if (this->verticeToInt.find(vertice) == this->verticeToInt.end()) {
        std::cout << "节点" + vertice + "不存在" << std::endl;
        return false;
    }
    for (int i = 0; i < this->verticeList.size(); i++) {
        if (i == this->verticeToInt[vertice])
            continue;
        if (this->distanceMatrix[this->verticeToInt[vertice]][i] != std::numeric_limits<double>::infinity()) {
            std::cout << this->verticeList[i] << " ";
        }
        std::cout << std::endl;
    }
    return true;
}

bool Graph::neighbors(const int vertice) const {
    if (vertice >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(vertice) + "不存在" << std::endl;
        return false;
    }
    for (int i = 0; i < this->verticeList.size(); i++) {
        if (i == vertice)
            continue;
        if (this->distanceMatrix[vertice][i] != std::numeric_limits<double>::infinity()) {
            std::cout << this->verticeList[i] << " ";
        }
        std::cout << std::endl;
    }
    return true;
}

bool Graph::insertVertice(const std::string &vertice) {
    if (this->verticeToInt.find(vertice) != this->verticeToInt.end()) {
        return false;
    }
    this->verticeList.push_back(vertice);
    this->verticeToInt[vertice] = static_cast<int>(this->verticeToInt.size());
    this->distanceMatrix.emplace_back(this->verticeList.size() - 1, std::numeric_limits<double>::max());
    for (int i = 0; i < this->verticeList.size(); i++) {
        this->distanceMatrix[i].push_back(std::numeric_limits<double>::infinity());
    }
    return true;
}

bool Graph::deleteVertice(const std::string &vertice) {
    if (this->verticeToInt.find(vertice) == this->verticeToInt.end()) {
        std::cout << "节点" + vertice + "不存在" << std::endl;
        return false;
    }
    for (int i = 0; i < this->verticeList.size(); i++) {
        this->distanceMatrix[i].erase(this->distanceMatrix[i].begin() + this->verticeToInt[vertice]);
    }
    this->distanceMatrix.erase(this->distanceMatrix.begin() + this->verticeToInt[vertice]);
    this->verticeList.erase(this->verticeList.begin() + this->verticeToInt[vertice]);
    this->verticeToInt.erase(vertice);
    return true;
}

bool Graph::deleteVertice(const int vertice) {
    if (vertice >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(vertice) + "不存在" << std::endl;
        return false;
    }
    for (int i = 0; i < this->verticeList.size(); i++) {
        this->distanceMatrix[i].erase(this->distanceMatrix[i].begin() + vertice);
    }
    this->distanceMatrix.erase(this->distanceMatrix.begin() + vertice);
    this->verticeToInt.erase(this->verticeList[vertice]);
    this->verticeList.erase(this->verticeList.begin() + vertice);
    return true;
}

bool Graph::addEdge(const std::string &start, const std::string &end, const double weight) {
    if (this->verticeToInt.find(start) == this->verticeToInt.end()) {
        std::cout << "节点" + start + "不存在" << std::endl;
        return false;
    }
    if (this->verticeToInt.find(end) == this->verticeToInt.end()) {
        std::cout << "节点" + end + "不存在" << std::endl;
        return false;
    }
    if (this->distanceMatrix[this->verticeToInt[start]][this->verticeToInt[end]] != std::numeric_limits<
            double>::infinity()) {
        std::cout << "边" + start + "-" + end + "已存在" << std::endl;
        return false;
    }
    this->distanceMatrix[this->verticeToInt[start]][this->verticeToInt[end]] = weight;
    return true;
}

bool Graph::addEdge(const int start, const int end, const double weight) {
    if (start >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(start) + "不存在" << std::endl;
        return false;
    }
    if (end >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(end) + "不存在" << std::endl;
        return false;
    }
    if (this->distanceMatrix[start][end] != std::numeric_limits<double>::infinity()) {
        std::cout << "边" + std::to_string(start) + "-" + std::to_string(end) + "已存在" << std::endl;
        return false;
    }
    this->distanceMatrix[start][end] = weight;
    return true;
}

bool Graph::deleteEdge(const std::string &start, const std::string &end) {
    if (this->verticeToInt.find(start) == this->verticeToInt.end()) {
        std::cout << "节点" + start + "不存在" << std::endl;
        return false;
    }
    if (this->verticeToInt.find(end) == this->verticeToInt.end()) {
        std::cout << "节点" + end + "不存在" << std::endl;
        return false;
    }
    if (this->distanceMatrix[this->verticeToInt[start]][this->verticeToInt[end]] == std::numeric_limits<
            double>::infinity()) {
        std::cout << "边" + start + "-" + "end" + "不存在" << std::endl;
    }
    this->distanceMatrix[this->verticeToInt[start]][this->verticeToInt[end]] = std::numeric_limits<double>::infinity();
    return true;
}

bool Graph::deleteEdge(const int start, const int end) {
    if (start >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(start) + "不存在" << std::endl;
        return false;
    }
    if (end >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(end) + "不存在" << std::endl;
        return false;
    }
    if (this->distanceMatrix[start][end] == std::numeric_limits<double>::infinity()) {
        std::cout << "边" + std::to_string(start) + "-" + std::to_string(end) + "不存在" << std::endl;
        return false;
    }
    this->distanceMatrix[start][end] = std::numeric_limits<double>::infinity();
    return true;
}

bool Graph::clearEdge() {
    for (int i = 0; i < this->verticeList.size(); i++) {
        for (int j = 0; j < this->verticeList.size(); j++) {
            this->distanceMatrix[i][j] = std::numeric_limits<double>::infinity();
        }
    }
    return true;
}

int Graph::firstNeighbor(const std::string &vertice) {
    if (this->verticeToInt.find(vertice) == this->verticeToInt.end()) {
        std::cout << "节点" + vertice + "不存在" << std::endl;
        return -1;
    }
    for (int i = 0; i < verticeList.size(); i++) {
        if (i == this->verticeToInt[vertice]) {
            continue;
        }
        if (this->distanceMatrix[this->verticeToInt[vertice]][i] != std::numeric_limits<double>::infinity()) {
            return i;
        }
    }
    std::cout << "节点" + vertice + "没有邻居" << std::endl;
    return -1;
}

int Graph::firstNeighbor(const int vertice) const {
    if (vertice >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(vertice) + "不存在" << std::endl;
        return -1;
    }
    for (int i = 0; i < verticeList.size(); i++) {
        if (i == vertice) {
            continue;
        }
        if (this->distanceMatrix[vertice][i] != std::numeric_limits<double>::infinity()) {
            return i;
        }
    }
    std::cout << "节点" + std::to_string(vertice) + "没有邻居" << std::endl;
    return -1;
}


int Graph::nextNeighbor(const std::string &vertice, const std::string &from) {
    if (this->verticeToInt.find(vertice) == this->verticeToInt.end()) {
        std::cout << "节点" + vertice + "不存在" << std::endl;
        return -1;
    }
    if (this->verticeToInt.find(from) == this->verticeToInt.end()) {
        std::cout << "节点" + from + "不存在" << std::endl;
        return -1;
    }
    for (int i = this->verticeToInt[from] + 1; i < this->verticeList.size(); i++) {
        if (i == this->verticeToInt[vertice]) {
            continue;
        }
        if (this->distanceMatrix[this->verticeToInt[vertice]][i] != std::numeric_limits<double>::infinity()) {
            return i;
        }
    }
    std::cout << "节点" + vertice + "没有" + from + "之后的邻居" << std::endl;
    return -1;
}

int Graph::nextNeighbor(const int vertice, const int from) const {
    if (vertice >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(vertice) + "不存在" << std::endl;
        return -1;
    }
    if (from >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(from) + "不存在" << std::endl;
        return -1;
    }
    for (int i = from + 1; i < this->verticeList.size(); i++) {
        if (i == vertice) {
            continue;
        }
        if (this->distanceMatrix[vertice][i] != std::numeric_limits<double>::infinity()) {
            return i;
        }
    }
    std::cout << "节点" + std::to_string(vertice) + "没有" + std::to_string(from) + "之后的邻居" << std::endl;
    return -1;
}

double Graph::getEdgeWeight(const std::string &start, const std::string &end) {
    if (this->verticeToInt.find(start) == this->verticeToInt.end()) {
        std::cout << "节点" + start + "不存在" << std::endl;
        return -1;
    }
    if (this->verticeToInt.find(end) == this->verticeToInt.end()) {
        std::cout << "节点" + end + "不存在" << std::endl;
        return -1;
    }
    return this->distanceMatrix[this->verticeToInt[start]][this->verticeToInt[end]];
}

double Graph::getEdgeWeight(const int start, const int end) const {
    if (start >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(start) + "不存在" << std::endl;
        return -1;
    }
    if (end >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(end) + "不存在" << std::endl;
        return -1;
    }
    return this->distanceMatrix[start][end];
}


bool Graph::setEdgeWeight(const std::string &start, const std::string &end, const double weight) {
    if (this->verticeToInt.find(start) == this->verticeToInt.end()) {
        std::cout << "节点" + start + "不存在" << std::endl;
        return false;
    }
    if (this->verticeToInt.find(end) == this->verticeToInt.end()) {
        std::cout << "节点" + end + "不存在" << std::endl;
        return false;
    }
    this->distanceMatrix[this->verticeToInt[start]][this->verticeToInt[end]] = weight;
    return true;
}

bool Graph::setEdgeWeight(const int start, const int end, const double weight) {
    if (start >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(start) + "不存在" << std::endl;
        return false;
    }
    if (end >= this->verticeList.size()) {
        std::cout << "节点" + std::to_string(end) + "不存在" << std::endl;
        return false;
    }
    this->distanceMatrix[start][end] = weight;
    return true;
}
