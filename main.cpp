#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include "include/City.h"
#include "include/Crossroad.h"


int main() {
    int N;
    int M;
    std::cin >> N >> M;

    std::vector<std::vector<std::string>> city;
    for(int i = 0; i < M; ++i){
        std::vector<std::string> _road;
        for(int j = 0; j < 3  ; ++j){
            std::string x;
            std::cin >>  x;
            _road.push_back(x);
        }
        city.push_back(_road);
    }

    std::unordered_set<std::string> crossroads_set;
    for(auto it : city){
        crossroads_set.insert(it[0]);
        crossroads_set.insert(it[1]);
    }

    std::vector<char> crossroads;
    for(auto it : crossroads_set){
        crossroads.push_back(it[0]);
    }
    std::sort(crossroads.begin(), crossroads.end());
    City new_city(N, crossroads, city);

    while (true){
        std::string command;
        std::cin >> command;
        int k;
        if(command == "add_bus"){
            std:: cin >> k;
            std::vector<Crossroad> stops;
            while(k-- >= 0) {
                char b;
                std::cin >> b;
                stops.push_back(Crossroad(b));
            }
            new_city.add_bus(stops);
        }

        else if(command == "Construct_crossroad"){
            std::cin >> k;
            int distance;
            char crossroad;
            std::vector<std::pair<char,int>> arguments;
            while(k-- > 0) {
                std::cin >> crossroad;
                std::cin >> distance;
                arguments.push_back(std::make_pair(crossroad,distance));
            }
            int m;
            std::cin >> m;
            while(m-- > 0){
                std::cin >> crossroad;
                std::cin >> distance;
                arguments.push_back(std::make_pair(crossroad,distance));
            }

            new_city.Construct_crossroad(arguments, k, m);
        }

        else if(command == "common_streets"){
            int i, j;
            std::cin >> i >> j;
            auto commons = new_city.common_streets(i,j);
            for(auto i : commons)
            {
                std::cout << i.getDestination()->getValue() << " " << i.getSource()->getValue() << std::endl;
            }
        }

        else if(command == "exit"){
            break;
        }
        else{
            std::cout << "Unknown command" << std::endl;
            continue;
        }

        new_city.Print_Matrix();
    }

    return 0;
}