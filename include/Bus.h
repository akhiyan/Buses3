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
    std::vector<Crossroad> path;
//    static int number;

public:
    Bus(std::vector<Crossroad> _path){
//        number = -1;
//        number++;
        for(int i = 0; i < _path.size(); ++i){
            path.push_back(_path[i]);
        }
    }

    bool path_contains(char element){
        for(int i = 0; i < path.size(); ++i)
        {
            if(path[i].getValue() == element)
            {
                return true;
            }
        }

        return false;
    }

    void Print_Path()
    {
        for(int i = 0; i < path.size(); ++i)
        {
            std::cout << path[i].getValue();
        }
    }
};


#endif //UNTITLED_BUS_H
