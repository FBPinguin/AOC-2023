//
// Created by floris on 5/23/25.
//


#include <iostream>

#include "Solution.h"



Solution::Position Solution::dir_to_pos(dir direction) {
   switch (direction) {
       case up:
           return {0,-1};
           break;
       case down:
           return {0,1};
           break;
       case left:
           return {-1,0};
           break;
       case right:
           return {1,0};
           break;
   }
}

int Solution::calculate_solution_1(){


    Position lastPos{0,0};
    int area = 0;
    for (auto& [dir, nSteps, _] : instructions) {
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
