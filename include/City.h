
#ifndef UNTITLED_CITY_H
#define UNTITLED_CITY_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <utility>
#include "Road.h"
#include "Bus.h"
#include "Crossroad.h"

#define INFINITY 1000000

class City{
private:
    std::unordered_map<char, Crossroad> allCrossroads;
    std::set<char, std::less<char>> crossroad_names;
    std::vector<std::vector<int>> adj_matrix;
    std::vector<std::vector<int>> adj_matrix_old;
    std::vector<Road*> roads;
    std::vector<Bus*> buses;

    void floydWarshall(std::vector<std::vector<int>>& adj);

public:

    City(int N, std::vector<char> crossroads, std::vector<std::vector<std::string>> _city);

    ~City();

    std::vector<std::pair<char,char>> getShortestPaths(const char& crossroadvalue, Bus& b);

    void update_matrix();

    void Construct_crossroad(std::vector<std::pair<char,int>> streets);

    Crossroad& getCrossroad(const char& name);

    void Add_road(char root, char destination, int distance);

    void add_bus(std::vector<Crossroad> stops);

    std::vector<Road> common_streets(int i, int j);

    std::pair<Crossroad*, int> find_closest_dest(Crossroad& start, Bus* b);

    void build_path(Crossroad& current_stop, Bus* b);

    void Print_Matrix();

    void initDijkstra(Crossroad *sourceNode);

    void dijkstra(Crossroad *startNode);

    void dijkstra(const char &startNodeValue);

    void relax(Road* road);
};

#endif //UNTITLED_CITY_H