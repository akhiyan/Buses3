
#ifndef UNTITLED_CITY_H
#define UNTITLED_CITY_H

#include <iostream>
#include <vector>
#include "Road.h"

#define INFINITY 1000000

class City{
private:
    std::vector<char> crossroads;
    std::vector<std::vector<int>> adj_matrix;


public:

    City(int N, std::vector<char> roads, std::vector<std::vector<std::string>> _city) : adj_matrix(N) {
        for(int i = 0; i < roads.size(); ++i){
            crossroads.push_back(roads[i]);
        }

        for(int i = 0; i < N; ++i)
        {
            adj_matrix[i].resize(N);
        }

        for(int i = 0; i < _city.size(); ++i){
            Add_road(_city[i][0][0], _city[i][1][0], std::stoi(_city[i][2]));
        }
    }

    void Add_road(char root, char destination, int distance){
        adj_matrix[root  - 'A'][destination - 'A'] = distance;
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
                std::cout << adj_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif //UNTITLED_CITY_H
