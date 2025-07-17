//
// Created by floris on 5/23/25.
//


#include "Solution.h"

long long Solution::calculate_solution_2(){

    Position lastPos{0,0};
    long area = 0;
    for (auto& [dir, nSteps, _] : instructions_p2) {
        Position Dir = dir_to_pos(dir);
        Dir *= nSteps;
        Position newPos = lastPos + Dir;

        area += (lastPos.y + newPos.y)*(lastPos.x-newPos.x) + nSteps;

        lastPos = newPos;
    }
    area /= 2;
    area += 1;
    return area;
}

