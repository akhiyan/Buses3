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
//    char label;

public:
    Road(int& _distance, Crossroad* _root, Crossroad* _destination) : distance(_distance), root(_root), destination(_destination){}

    Crossroad *getSource() const {
        return root;
    }

    Crossroad *getDestination() const {
        return destination;
    }

//    char getLabel() const {
//        return label;
//    }


//    void setLabel(const char &lbl) {
//        label = lbl;
//    }

    bool operator==(const Road &other) const {
        return root == other.root && destination == other.destination; //&& label == other.label;
    }

//
//    void setLabel(const char &lbl) {
//        label = lbl;
//    }
//
//    bool operator==(const Road &other) const {
//        return root == other.root && destination == other.destination && label == other.label;
//    }


};

#endif //UNTITLED_ROAD_H
