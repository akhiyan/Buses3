#include <iostream>
#include <string>
#include <vector>
#include "Include/City.h"

int main() {
    int N = 4;
    int M = 6;

    std::vector<std::vector<std::string>> city = {{"A","B","3"}, {"B","D","2"},{"D","C","1"},{"C","A","4"},{"D","A","5"},{"B","C","6"}};
    std::vector<char> crossroads = {'A', 'B', 'C', 'D'};
    City my_city(4,crossroads, city);
    my_city.Print_Matrix();

    return 0;
}
