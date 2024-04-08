//
// Created by Admin on 4/6/2024.
//
#include "../include/Bus.h"

Bus::Bus(std::vector<Crossroad> _path){
    //number = -1;
    //number++;
    for(int i = 0; i < _path.size(); ++i){
    stops.push_back(_path[i]);
    }
}
Bus::~Bus()
{
    //number--;
}
bool Bus::path_contains(char element){
    for(int i = 0; i < stops.size(); ++i)
    {
        if(stops[i].getValue() == element)
        {
            return true;
        }
    }

    return false;
}

void Bus::add_path(Crossroad& stop){
    path.push_back(stop);
}

Crossroad Bus::get_stop(int index) const
{
    return path[index];
}

void Bus::Print_Path(){
    for(int i = 0; i < path.size(); ++i)
    {
        std::cout << path[i].getValue();
    }
}