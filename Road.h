//
// Created by a_akh on 3/20/2024.
//

#ifndef UNTITLED_ROAD_H
#define UNTITLED_ROAD_H

class Road
{
private:
    int distance;
    Road* root;
    std::vector<Road*> destinations;

public:
    Road(int& _distance, char& _root, char& destination) : distance(_distance) {}
};

#endif //UNTITLED_ROAD_H
