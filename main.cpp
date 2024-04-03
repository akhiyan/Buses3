#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include "include/City.h"
#include "include/Bus.h"
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

    City new_city(N, crossroads, city);

    while (true){
        std::string command;
        std::cin >> command;
        if(command == "add_bus"){
            int k;
            std:: cin >> k;
            std::vector<Crossroad> stops;
            for(int i = 0; i < k + 1; ++i){
                char b;
                std::cin >> b;
                stops.push_back(Crossroad(b));
            }
            new_city.add_bus(stops);
            //new_city.Print_Matrix();
        }

        else if(command == "Construct_crossroad"){

        }

        else if(command == "common_streets"){

        }

        else if(command == "exit"){
            break;
        }
        else{
            std::cout << "Unknown command" << std::endl;
            std::cout << "Exiting...";
            break;
        }
    }

    return 0;
}
