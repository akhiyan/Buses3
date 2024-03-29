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
<<<<<<< HEAD

//    void setLabel(const char &lbl) {
//        label = lbl;
//    }

    bool operator==(const Road &other) const {
        return root == other.root && destination == other.destination; //&& label == other.label;
    }
=======
//
//    void setLabel(const char &lbl) {
//        label = lbl;
//    }
//
//    bool operator==(const Road &other) const {
//        return root == other.root && destination == other.destination && label == other.label;
//    }
>>>>>>> 511008846a3a25bbf7d8ea62d541d442b84889c0

};

#endif //UNTITLED_ROAD_H
