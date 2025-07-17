//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <fstream>
#include <vector>

class Solution{

    struct Position {
        long x;
        long y;

        Position operator+(Position& other) {
            return {x+other.x, y+other.y};
        }

        Position& operator*=(int i) {
            x *= i;
            y *= i;
            return *this;
        }
    };

    enum dir {
        up,
        down,
        left,
        right
    };

    struct Instruction {
        dir direction;
        int nSteps;
        int hexColor;
    };

    std::vector<Instruction> instructions;

    std::vector<Instruction> instructions_p2;


public:
    void init(std::ifstream& input);

    int calculate_solution_1();

    long long calculate_solution_2();

    Position dir_to_pos(dir direction);


};

#endif //SOLUTION_H
