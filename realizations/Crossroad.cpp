#include "../include/Crossroad.h"

Crossroad::Crossroad(const char &val) : value(val), visited(false) {}
Crossroad::Crossroad() {}
//Crossroad(const char &other) : value(other.value) {}

char Crossroad::getValue() const {
    return value;
}

int Crossroad::getDistance() const {
    return distance;
}

void Crossroad::visit(){
    visited = true;
}

void Crossroad::reset_visit() {
    visited = false;
}

bool Crossroad::is_visited() const{
    return  visited;
}

std::vector<char> Crossroad::getPath()
{
    std::vector<char> result;
    result.push_back(value);
    Crossroad * tmp = parent;
    while (parent != nullptr)
    {
        result.push_back(parent->value);
        parent = parent->parent;
    }

    parent = tmp;

    return result;
}

void Crossroad::setDistance(int newDistance) {
    distance = newDistance;
}

void Crossroad::setParent(Crossroad *newParent) {
    parent = newParent;
}

bool Crossroad::operator==(const Crossroad &other) const {
    return value == other.value;
}

void Crossroad::print() const {
    std::cout << "Crossroad: " << getValue()
              << std::endl;
}