//
// Created by floris on 5/23/25.
//


#include "Solution.h"

int Solution::calculate_solution_2(){
    int max = 0;

    for (int i = 0; i < mapCols; ++i) {
        max = std::max(max, calculate_solution_1({i, 0}, S));
        max = std::max(max, calculate_solution_1({i, mapRows-1}, N));
    }
    for (int i = 0; i < mapRows; ++i) {
        max = std::max(max, calculate_solution_1({0, i}, E));
        max = std::max(max, calculate_solution_1({mapCols-1, i}, W));
    }

    return max;
}
