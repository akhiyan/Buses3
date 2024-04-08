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
    unsigned number;

public:
    Bus(std::vector<Crossroad> _path, unsigned _number);

    int get_number() const;

    void reset_path();

    bool path_contains(char element);

    void add_path(Crossroad& stop);

    Crossroad& get_stop(int index);

    void Print_Path();
};
;

#endif //UNTITLED_BUS_H
