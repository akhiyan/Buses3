
#ifndef UNTITLED_CITY_H
#define UNTITLED_CITY_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
#include <utility>
#include "Road.h"
#include "Bus.h"
#include "Crossroad.h"

#define INFINITY 1000000

class City{
private:
    std::unordered_map<char, Crossroad> allNodes;
    std::set<char, std::less<char>> crossroad_names;
    std::vector<std::vector<int>> adj_matrix;
    std::vector<std::vector<int>> adj_matrix_old;
    std::vector<Road> roads;
    std::vector<Bus> buses;

    void floydWarshall(std::vector<std::vector<int>>& adj);

public:

    City(int N, std::vector<char> crossroads, std::vector<std::vector<std::string>> _city);

    void Construct_crossroad(std::vector<std::pair<char,int>> streets);

    Crossroad getCrossroad(char& name);

    void Add_road(char root, char destination, int distance);

    void add_bus(std::vector<Crossroad> stops);

    void common_streets(int i, int j);

    std::pair<Crossroad, int> find_closest_dest(Crossroad& start, Bus& b);

    void build_path(Crossroad& current_stop, Bus& b);

    void Print_Matrix();

//    void initDijkstra(Crossroad *sourceNode) {
//        for (auto node: allNodes) {
//            node.second->setDistance(INT_MAX);
//            node.second->setParent(nullptr);
//        }
//        sourceNode->setDistance(0);
//    }
//
//    void dijkstra(Crossroad *startNode) {
//        initDijkstra(startNode);
//        std::unordered_set<Crossroad*> q;
//        for (auto node: allNodes) {
//            q.insert(node.second);
//        }
//
//        while (!q.empty()) {
//            Crossroad* minNode = nullptr;
//            int minDistance = INT_MAX;
//            for (auto node: q) {
//                if (minDistance > node->getDistance()) {
//                    minDistance = node->getDistance();
//                    minNode = node;
//                }
//            }
//            if (minNode == nullptr) {
//                return;
//            }
//            q.erase(minNode);
//
//            for (auto edge: out_edges[minNode]) {
//                relax(edge);
//            }
//        }
//    }
//
//    void dijkstra(const char &startNodeValue) {
//        auto sourceNode = getNode(startNodeValue);
//        if (sourceNode != nullptr) {
//            dijkstra(sourceNode);
//        }
//    }
//
//    void relax(Road &edge) {
//        auto source = edge.getSource();
//        auto dest = edge.getDestination();
//
//        if (source->getDistance() + edge.getLabel() < dest->getDistance()) {
//            dest->setDistance(source->getDistance() + edge.getLabel());
//            dest->setParent(source);
//        }
//    }
};

#endif //UNTITLED_CITY_H