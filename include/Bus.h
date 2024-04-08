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
    std::vector<Crossroad> stops;
    //static int number;

public:
    Bus(std::vector<Crossroad> _path);

    ~Bus();

    bool path_contains(char element);

    void add_path(Crossroad& stop);

    Crossroad get_stop(int index) const;

    void Print_Path();
};

//int Bus::number = -1;

#endif //UNTITLED_BUS_H