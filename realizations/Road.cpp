#include "../include/Road.h"

Road::Road(Crossroad* _root, Crossroad* _destination, int& _length) : root(_root), destination(_destination), length(_length){}

Crossroad* Road::getSource() const {
    return root;
}

Crossroad* Road::getDestination() const {
    return destination;
}

char Road::getLength() const {
    return length;
}


void Road::setLength(const char &lth) {
    length = lth;
}

bool Road::operator==(const Road &other) const {
    return root == other.root && destination == other.destination && length == other.length;
}
