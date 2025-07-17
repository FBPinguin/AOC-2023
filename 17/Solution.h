//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <fstream>
#include <limits.h>
#include <set>
#include <unordered_set>
#include <vector>


struct position {
    int x;
    int y;

    bool operator==(const position &other) const {
        return x == other.x && y == other.y;
    }
    position operator+(const position &other) const {
        return {x + other.x, y + other.y};
    }

    position operator*(const int i) const {
        return {x*i, y*i};
    }
};
struct state {
    position pos;
    int val;
    position lastMove;
    int numOfMove;
    bool operator>(const state& other) const { return val > other.val; } // For min-heap
};


class Solution{


public:
    void init(std::ifstream& input);

    int calculate_solution_1();

    int calculate_solution_2();

private:
    std::vector<std::vector<char>> heatMap;
    int minVal{INT_MAX};

    int CalculateShortestPath();

    bool isValidPos(const __gnu_cxx::__alloc_traits<std::allocator<state>>::value_type &value, position move);




};

#endif //SOLUTION_H
