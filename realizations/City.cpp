#include "../include/City.h"

void City::floydWarshall(std::vector<std::vector<int>>& adj) {
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
}

City::City(int N, std::vector<char> crossroads, std::vector<std::vector<std::string>> _city) : adj_matrix(N) {
    for(int i = 0; i < crossroads.size(); ++i)
    {
        allCrossroads[crossroads[i]] = Crossroad(crossroads[i]);
        crossroad_names.insert(crossroads[i]);
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

std::vector<std::pair<char,char>> City::getShortestPaths(const char& crossroadvalue, Bus& b){
    std::vector<std::vector<char>> path_matrix;
    dijkstra(&allCrossroads[crossroadvalue]);
    for(auto crossroad : allCrossroads)
    {
        if(b.path_contains(crossroad.second.getValue()))
            path_matrix.push_back(crossroad.second.getPath());
    }

    std::vector<std::pair<char,char>> result;

    for(int i = 0; i < path_matrix.size(); ++i)
    {
        for(int j = 0; j < path_matrix.size() - 1; j+=2)
        {
            result.push_back(std::make_pair(path_matrix[i][j], path_matrix[i][j+1]));
        }
    }

    return  result;
}

void City::update_matrix(){

}

void City::Construct_crossroad(std::vector<std::pair<char,int>> streets){
    char name;
    for(char c = 'A'; c < 'Z'; ++c)
    {
        if(!crossroad_names.contains(c))
        {
            name = c;
            crossroad_names.insert(c);
            break;
        }
    }

    Crossroad new_crossroad = Crossroad(name);
    allCrossroads[name] = new_crossroad;

    int new_size = crossroad_names.size();

    for(int i = 0; i < adj_matrix.size(); ++i)
    {
        adj_matrix[i].resize(new_size);
        adj_matrix[i][new_size - 1] = INFINITY;
    }

    adj_matrix.push_back(std::vector<int>(crossroad_names.size()));
    for(int i = 0; i < adj_matrix[new_size - 1].size() - 1; ++i)
    {
        adj_matrix[new_size - 1][i] = INFINITY;
    }
    adj_matrix[new_size - 1][new_size - 1] = 0;

    for(int i = 0; i < streets.size(); ++i)
    {
        Add_road(streets[i].first, name, streets[i].second);
    }
}

Crossroad& City::getCrossroad(const char& name){
    return allCrossroads[name];
}

void City::Add_road(char root, char destination, int distance){
    adj_matrix[root  - 'A'][destination - 'A'] = distance;

    auto dest_crossroad = getCrossroad(root);
    auto root_crossroad = getCrossroad(destination);
    roads.push_back(Road(&root_crossroad, &dest_crossroad,distance));
}

void City::add_bus(std::vector<Crossroad> stops){
    Bus b = Bus(stops);
    buses.push_back(b);
    Crossroad first_stop = allCrossroads[stops[0].getValue()];
    std::pair<Crossroad,int> closest_dest = find_closest_dest(first_stop, b);
    std::cout << "Closest stop is " << closest_dest.first.getValue() << " and the distance from " << first_stop.getValue() << " is " << closest_dest.second;
    std::cout << std::endl;
    build_path(first_stop, b);
}

void City::common_streets(int i, int j)
{
    Bus& ith_bus = buses[i];
    Bus& jth_bus = buses[j];

    std::vector<std::pair<char,char>> bus_path1 = getShortestPaths(ith_bus.get_stop(0).getValue(), ith_bus);
    std::vector<std::pair<char,char>> bus_path2 = getShortestPaths(jth_bus.get_stop(0).getValue(), jth_bus);
    std::vector<std::pair<char,char>> common_dests;


    for(int k = 0; k < bus_path1.size(); ++k)
    {
        for(int f = 0; f < bus_path2.size(); ++f)
        {
            if(bus_path1[i].first == bus_path2[f].first &&
            bus_path1[i].second == bus_path2[f].second){
                common_dests.push_back(std::make_pair(bus_path1[i].first, bus_path2[j].second));
            }
        }
    }





}

std::pair<Crossroad, int> City::find_closest_dest(Crossroad& start, Bus& b)
{
    int min = INT_MAX;
    Crossroad closest_dest = NULL;
    int element;
    for(int i = 0; i < adj_matrix[start.getValue() - 'A'].size(); ++i){
        element = adj_matrix[start.getValue() - 'A'][i];
        if(element != 0 && b.path_contains('A' + i) && element < min && element != INFINITY)
        {
            closest_dest = allCrossroads['A' + i];
            min = element;
        }

    }
    return std::make_pair(closest_dest, min);
}

void City::build_path(Crossroad& current_stop, Bus& b)
{
    b.add_path(current_stop);
    Crossroad next_stop = find_closest_dest(current_stop,b).first;
    if(next_stop != NULL)
    {
        build_path(next_stop, b);
    }
}

void City::Print_Matrix(){
    int i;

    std::cout << "  ";
    for(auto i : crossroad_names) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto it = crossroad_names.begin();
    for(i = 0; i < adj_matrix.size(); ++i){
        std::cout << *it << " ";
        std::advance(it,1);

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

void City::initDijkstra(Crossroad *sourceCrossroad){
    for (auto crossroad: allCrossroads) {
        crossroad.second.setDistance(INT_MAX);
        crossroad.second.setParent(nullptr);
    }
    sourceCrossroad->setDistance(0);
}

void City::dijkstra(Crossroad *startCrossroad) {
    initDijkstra(startCrossroad);
    std::unordered_set<Crossroad*> q;
    for (auto crossroad: allCrossroads) {
        q.insert(&crossroad.second);
    }

    while (!q.empty()) {
        Crossroad* minCrossroad = nullptr;
        int minDistance = INT_MAX;
        for (auto crossroad: q) {
            if (minDistance > crossroad->getDistance()) {
                minDistance = crossroad->getDistance();
                minCrossroad = crossroad;
            }
        }
        if (minCrossroad == nullptr) {
            return;
        }
        q.erase(minCrossroad);

        for (auto road: roads) {
            relax(road);
        }
    }
}

void City::dijkstra(const char &startCrossroadValue) {
    Crossroad* sourceCrossroad = &getCrossroad(startCrossroadValue);
    if (sourceCrossroad != nullptr) {
        dijkstra(sourceCrossroad);
    }
}

void City::relax(Road &road) {
    auto source = road.getSource();
    auto dest = road.getDestination();

    if (source->getDistance() + road.getLength() < dest->getDistance()) {
        dest->setDistance(source->getDistance() + road.getLength());
        dest->setParent(source);
    }
}