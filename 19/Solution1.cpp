//
// Created by floris on 5/23/25.
//


#include <iostream>

#include "Solution.h"

int Solution::calculate_solution_1(){

    int acc{0};

    for (auto& item : all_items) {
        std::string next = move_through_workflow(all_workflows["in"], item);

        while (next != "R" && next != "A") {
            next = move_through_workflow(all_workflows[next], item);
        }
        if (next == "A") {
           acc += item.valueMap[m] + item.valueMap[x] + item.valueMap[a] + item.valueMap[s];
        }


    }


    return acc;
}

