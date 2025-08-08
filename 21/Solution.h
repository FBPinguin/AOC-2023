//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <array>
#include <fstream>

#include "util.h"

class Solution {
    struct Direction {
        int x;
        int y;

        Direction operator+(Direction other) const {
            return {x + other.x, y + other.y};
        }

        bool operator==(const Direction &other) const {
            return x==other.x && y==other.y;
        }
    };

    class direction_hash {
    public:
        std::size_t operator()(const Direction dir) const {
            return std::hash<int>()(dir.x) ^ std::hash<int>()(dir.y);
        }
    };

    std::vector<Direction> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};


    util::charMap garden;

public:
    void init(std::ifstream &input);

    int calculate_solution_1();

    int calculate_solution_2();

private:
    bool is_inbounds(Direction dir);
    bool is_inbounds_p2(Direction dir);
};

#endif //SOLUTION_H
