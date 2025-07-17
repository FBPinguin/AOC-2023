//
// Created by floris on 5/23/25.
//


#include "Solution.h"

int Solution::calculate_solution_2() {
    int loops{1000};

    total_send = {{low, 0}, {high, 0}};
    work_list.clear();

    for (int i = 0; i < loops; ++i) {
        pushButton();
        total_send[low] += 1;

        while (!work_list.empty()) {
            SignalTask curTask = work_list.front();
            handleTask(curTask);
            work_list.erase(work_list.begin());
        }
    }


    return total_send[low] * total_send[high];
}
