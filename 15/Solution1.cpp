//
// Created by floris on 5/23/25.
//


#include <iostream>
#include <ranges>

#include "Solution.h"

int Solution::calculate_solution_1(std::ifstream& input){
    int currValue{0};
    int acc{0};
    auto it = std::ranges::istream_view<char>{input};
    for (char& c : it) {
        if (c == ',' || c == '\n') {
            acc += currValue;
            currValue = 0;
            continue;
        }
        currValue = ((currValue + c)*17)%256;
    }
    acc += currValue;

    return acc;
}
