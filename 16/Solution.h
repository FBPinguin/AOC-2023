//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <fstream>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "util.h"

enum dir {
    N,
    E,
    S,
    W,
};

class Solution{

    struct state {
        std::pair<int,int> pos;
        std::pair<int,int> dir;

        bool operator==(const state& other) const {
            return pos == other.pos && dir == other.dir;
        }
    };

    struct hash_state {
        std::size_t operator()(const state& s) const {
            std::size_t h1 = std::hash<int>()(s.pos.first);
            std::size_t h2 = std::hash<int>()(s.pos.second);
            std::size_t h3 = std::hash<int>()(s.dir.first);
            std::size_t h4 = std::hash<int>()(s.dir.second);

            // Combine hashes (standard technique)
            std::size_t hash = h1;
            hash ^= h2 + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= h3 + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            hash ^= h4 + 0x9e3779b9 + (hash << 6) + (hash >> 2);

            return hash;
        }
    };
    struct hash_pair {
        template <class T1, class T2>
        size_t operator()(const std::pair<T1, T2>& p) const
        {
            // Hash the first element
            size_t hash1 = std::hash<T1>{}(p.first);
            // Hash the second element
            size_t hash2 = std::hash<T2>{}(p.second);
            // Combine the two hash values
            return hash1
                   ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                      + (hash1 >> 2));
        }
    };



public:


    void init(std::ifstream& input);

    int calculate_solution_1(std::pair<int,int> position, dir direction);

    void moveTowardsDirection(std::pair<int,int> position,dir direction);

    int calculate_solution_2();

private:
    util::charMap map;
    size_t mapRows;
    size_t mapCols;
    std::set<std::pair<std::pair<int,int>,dir>> seen;
    std::set<std::pair<int,int>> beenTo;


};

#endif //SOLUTION_H
