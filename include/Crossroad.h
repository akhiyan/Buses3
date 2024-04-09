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
    bool visited;

public:
    Crossroad(const char &val);

    Crossroad();
    //Crossroad(const char &other) : value(other.value) {}

    char getValue() const;

    int getDistance() const;

    void visit();

    void reset_visit();

    bool is_visited() const;

    std::vector<char> getPath();
    void setDistance(int newDistance);

    void setParent(Crossroad *newParent);

    bool operator==(const Crossroad &other) const;

    void print() const;
};

#endif //BUSES3_CROSSROAD_H
