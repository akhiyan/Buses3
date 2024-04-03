
#ifndef UNTITLED_CITY_H
#define UNTITLED_CITY_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "Road.h"
#include "Bus.h"
#include "Crossroad.h"

#define INFINITY 1000000

class City{
private:
    std::unordered_map<char, Crossroad> allNodes;
    std::vector<std::vector<int>> adj_matrix;
    std::vector<std::vector<int>> adj_matrix_old;
    std::vector<Road> roads;
    std::vector<Bus> buses;

    std::vector<std::vector<int>> floydWarshall(std::vector<std::vector<int>>& adj) {
        for (int k = 0; k < adj.size(); k++) {
            for (int i = 0; i < adj.size(); i++) {
                for (int j = 0; j < adj.size(); j++) {
                    if (adj[i][k] + adj[k][j] < adj[i][j] &&
                        (adj[i][k] != INFINITY) && (adj[k][j] != INFINITY)) {
                        adj[i][j] = adj[i][k] + adj[k][j];

                    }
                }
            }
        }
        return adj_matrix;
    }

public:

    City(int N, std::vector<char> crossroads, std::vector<std::vector<std::string>> _city) : adj_matrix(N) {
        for(int i = 0; i < crossroads.size(); ++i)
        {
            allNodes[crossroads[i]] = Crossroad(crossroads[i]);
        }

        for(int i = 0; i < N; ++i)
        {
            adj_matrix[i].resize(N);
            for (int j = 0; j < N; ++j){
                if(i != j){
                    adj_matrix[i][j] = INFINITY;
                }
            }
        }

        for(int i = 0; i < _city.size(); ++i){
            Add_road(_city[i][0][0], _city[i][1][0], std::stoi(_city[i][2]));
        }

        adj_matrix_old = adj_matrix;
        floydWarshall(adj_matrix);
    }

    void Construct_crossroad(std::vector<std::pair<char,char>> streets){
        for(int i = 0; i < adj_matrix.size() - 1; ++i)
        {
            adj_matrix[i].push_back(INFINITY);
        }
        adj_matrix[adj_matrix.size() - 1].push_back(0);
        allNodes[adj_matrix.size() - 1 + 'i'];
        std::cout << "Added crossroad " << adj_matrix.size() - 1 + 'i' << std::endl;

        for(int i = 0; i < streets.size(); ++i){
            Add_road(streets[i].first, streets[i].second, -1);
        }

    }

    Crossroad getCrossroad(char& name){
        return allNodes[name];
    }

    void Add_road(char root, char destination, int distance){
        adj_matrix[root  - 'A'][destination - 'A'] = distance;

        auto dest_crossroad = getCrossroad(root);
        auto root_crossroad = getCrossroad(destination);
        roads.push_back(Road(distance, &root_crossroad, &dest_crossroad));
    }

    void add_bus(std::vector<Crossroad> stops){
        Bus b = Bus(stops);
       buses.push_back(b);
       Crossroad first_stop = allNodes[stops[0].getValue()];
       std::pair<Crossroad,int> closest_dest = find_closest_dest(first_stop, b);
       std::cout << "Closest stop is " << closest_dest.first.getValue() << " and the distance from " << first_stop.getValue() << " is " << closest_dest.second;
       std::cout << std::endl;
       build_path(first_stop, b);
    }

    void common_streets(int i, int j)
    {
        Bus ith_bus = buses[i];
        Bus jth_bus = buses[j];
        //std::cout << buses[i].get
    }

    std::pair<Crossroad, int> find_closest_dest(Crossroad& start, Bus& b)
    {
        int min = INT_MAX;
        Crossroad closest_dest = NULL;
        int element;
        for(int i = 0; i < adj_matrix[start.getValue() - 'A'].size(); ++i){
            element = adj_matrix[start.getValue() - 'A'][i];
            if(element != 0 && b.path_contains('A' + i) && element < min && element != INFINITY)
            {
                closest_dest = allNodes['A' + i];
                min = element;
            }

        }
            return std::make_pair(closest_dest, min);
    }

    void build_path(Crossroad& current_stop, Bus& b)
    {
        b.add_path(current_stop);
        Crossroad next_stop = find_closest_dest(current_stop,b).first;
        if(next_stop != NULL)
        {
            build_path(next_stop, b);
        }
    }

    void Print_Matrix(){
        int i;

        std::cout << "  ";
        for(i = 0; i < adj_matrix.size(); ++i) {
            std::cout << (char) ('A' + i) << " ";
        }
        std::cout << std::endl;

        for(i = 0; i < adj_matrix.size(); ++i){
            std::cout << (char)('A' + i) << " ";
            for(int j = 0; j < adj_matrix[i].size(); ++j){
                if(adj_matrix[i][j] == INFINITY){
                    std::cout << "- " ;
                    continue;
                }
                std::cout << adj_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

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
