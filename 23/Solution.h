#ifndef SOLUTION_H
#define SOLUTION_H

#include <fstream>
#include <functional>
#include <unordered_set>
#include "util.h"

class Solution {
public:
    struct Direction {
        int x;
        int y;
        bool operator==(const Direction& other) const {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Direction& other) const {
            return !(other == *this);
        }
    };

    class DirectionHash {
    public:
        size_t operator()(const Direction& dir) const {
            size_t hash = std::hash<int>()(dir.x);
            hash = hash * 31 + std::hash<int>()(dir.y);
            return hash;
        }
    };

    struct state {
        Direction pos;
        Direction last_step{0,1};
        int steps{0};
        std::unordered_set<Direction, DirectionHash> seen;
        // state() : pos{0, 0}, steps{0} {}
        // state(Direction p, int s) : pos(p), steps(s) {}
        // state(Direction p, Direction ls, int s, std::unordered_set<Direction, DirectionHash> sn) : pos(p),last_step(ls), steps(s),seen(sn){}
    };

public:
    void init(std::ifstream& input);
    bool can_pass(char hill, Direction dir);

    Direction get_ice_direction(char hill);

    void print_path_taken(state& state);

    int calculate_solution_1();
    int calculate_solution_2();

private:
    util::charMap map;
    size_t map_height, map_width;
    Direction start_pos{1, 0};
    Direction end_pos{0, 0};
};

#endif // SOLUTION_H