//
// Created by a_akh on 3/20/2024.
//

#ifndef UNTITLED_ROAD_H
#define UNTITLED_ROAD_H

#include "Crossroad.h"

class Road
{
private:
    int distance;
    Crossroad* root;
    Crossroad* destination;
    int length;


public:
    Road(Crossroad* _root, Crossroad* _destination, int _length);

    Crossroad* getSource() const;

    Crossroad *getDestination() const;

    char getLength() const ;

    void setLength(const char &lth);

    bool operator==(const Road &other) const;

};

#endif //UNTITLED_ROAD_H
