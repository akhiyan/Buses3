#ifndef BUSES3_CROSSROAD_H
#define BUSES3_CROSSROAD_H

#include <iostream>
#include <vector>

class Crossroad
{
private:
    char value;
    Crossroad* parent = nullptr;
    Crossroad* destination = nullptr;
    int distance = INT_MAX;

public:
    Crossroad(const char &val) : value(val) {}
    Crossroad() {}
    //Crossroad(const char &other) : value(other.value) {}

    char getValue() const {
        return value;
    }

    int getDistance() const {
        return distance;
    }

    std::vector<char> getPath()
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

    void setDistance(int newDistance) {
        distance = newDistance;
    }

    void setParent(Crossroad *newParent) {
        parent = newParent;
    }

    bool operator==(const Crossroad &other) const {
        return value == other.value;
    }

    void print() const {
        std::cout << "Crossroad: " << getValue()
                  << std::endl;
    }

    struct HashFunction {
        size_t operator()(const Crossroad &node) const {
            return std::hash<char>()(node.getValue());
        }
    };
};

#endif //BUSES3_CROSSROAD_H
