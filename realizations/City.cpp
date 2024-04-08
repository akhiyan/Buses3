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
        Add_road(name, streets[i].first, streets[i].second);
    }

    floydWarshall(adj_matrix);
//    int j = adj_matrix.size() - 1;
//    for(int k = 0; k < adj_matrix.size(); ++k){
//        for(int i = 0; i < adj_matrix.size(); ++i)
//        {
//            if (adj_matrix[i][k] + adj_matrix[k][j] < adj_matrix[i][j] &&
//                (adj_matrix[i][k] != INFINITY) && (adj_matrix[k][j] != INFINITY)) {
//                adj_matrix[i][j] = adj_matrix[i][k] + adj_matrix[k][j];
//
//            }
//        }
//    }

    recalculate_paths();

//    Crossroad start;
//    for(int i = 0; i < buses.size(); ++i)
//    {
//        start = buses[i].get_stop(0);
//        std::pair<Crossroad, int> closest_dest = find_closest_dest(start, buses[i]);
//        std::cout << "Bus number " <<buses[i].get_number() << " - " <<
//        "The closest destination is " << closest_dest.first.getValue() <<
//        " and the distance from " << start.getValue() << " is " << closest_dest.second << std::endl;
//    }

}

void City::recalculate_paths()
{
    for(int i = 0; i < buses.size(); ++i)
    {
        Crossroad& first_stop = buses[i].get_stop(0);
        buses[i].reset_path();
        build_path(first_stop, buses[i]);
    }
}


Crossroad* City::getCrossroad(const char& name){
    return &allCrossroads[name];
}

void City::Add_road(char root, char destination, int distance){
    adj_matrix[root  - 'A'][destination - 'A'] = distance;

    auto dest_crossroad = getCrossroad(root);
    auto root_crossroad = getCrossroad(destination);
    roads.push_back(Road(root_crossroad, dest_crossroad, distance));
}

void City::add_bus(std::vector<Crossroad> stops){
    Bus b = Bus(stops, buses.size());
    buses.push_back(b);
    Crossroad first_stop = allCrossroads[stops[0].getValue()];
    std::pair<Crossroad,int> closest_dest = find_closest_dest(first_stop, b);
    std::cout << "The closest stop is " << closest_dest.first.getValue() << " and the distance from " << first_stop.getValue() << " is " << closest_dest.second;
    std::cout << std::endl;
    build_path(first_stop, buses[buses.size() - 1]);
}

void City::common_streets(int i, int j)
{
    Bus ith_bus = buses[i];
    Bus jth_bus = buses[j];
    //std::cout << buses[i].get
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
    std::cout << "  ";
    for(auto i : crossroad_names) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto it = crossroad_names.begin();
    for(int i = 0; i < adj_matrix.size(); ++i){
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

void City::initDijkstra(Crossroad *sourceCrossroad) {
    for (auto crossroad: allCrossroads) {
        crossroad.second.setDistance(INT_MAX);
        crossroad.second.setParent(nullptr);
    }
    sourceCrossroad->setDistance(0);
}

void City::dijkstra(Crossroad *startCrossroad) {
    initDijkstra(startCrossroad);
    std::set<Crossroad*> c_set;
    for (auto crossroad: allCrossroads) {
        c_set.insert(&crossroad.second);
    }

    while (!c_set.empty()) {
        Crossroad* minCrossroad = nullptr;
        int minDistance = INT_MAX;
        for (auto crossroad: c_set) {
            if (minDistance > crossroad->getDistance()) {
                minDistance = crossroad->getDistance();
                minCrossroad = crossroad;
            }
        }
        if (minCrossroad == nullptr) {
            return;
        }
        c_set.erase(minCrossroad);

        for(auto road : roads)
        {
            if(*road.getSource() == minCrossroad->getValue())
            {
                relax(road);
            }
        }

    }
}

void City::dijkstra(const char &startNodeValue) {
    auto sourceCrossroad = getCrossroad(startNodeValue);
    if (sourceCrossroad != nullptr) {
        dijkstra(sourceCrossroad);
    }
}

void City::relax(Road &edge) {
    auto source = edge.getSource();
    auto dest = edge.getDestination();

    if (source->getDistance() + edge.getLength() < dest->getDistance()) {
        dest->setDistance(source->getDistance() + edge.getLength());
        dest->setParent(source);
    }
}