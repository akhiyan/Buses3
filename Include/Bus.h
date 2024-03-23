//
// Created by a_akh on 3/20/2024.
//

#ifndef UNTITLED_BUS_H
#define UNTITLED_BUS_H

#include <iostream>
#include "Road.h"
#include <vector>

class Bus
{
private:
    std::vector<Road> path;
    int number;

public:
    Bus(int _number, std::vector<Road> _path) : number(_number){
        for(int i = 0; i < _path.size(); ++i){
            path.push_back(_path[i]);
        }
    }
};


#endif //UNTITLED_BUS_H
