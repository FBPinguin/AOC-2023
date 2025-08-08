//
// Created by floris on 5/23/25.
//


#include <unordered_set>

#include "Solution.h"


bool Solution::is_inbounds(Direction dir) {
    if (dir.x < 0 || dir.y < 0) {
        return false;
    }
    if (dir.x >= garden[0].size() || dir.y >= garden.size()) {
        return false;
    }
    return true;
}


int Solution::calculate_solution_1() {
    int steps[]{0, 1};
    Direction init_pos;

    for (int i = 0; i < garden.size(); ++i) {
        for (int j = 0; j < garden[0].size(); ++j) {
            if (garden[i][j] == 'S') {
                init_pos = {i, j};
            }
        }
    }

    bool is_odd_step = false;
    std::vector<Direction> worklist{init_pos};
    std::unordered_set<Direction, direction_hash> seen;
    int iteration = 0;
    int total_iterations = 64;

    int vec_index{0};
    while (iteration < total_iterations) {
        int acc{0};
        std::vector<Direction> newWorkList;

        for (auto cur_dir: worklist) {
            for (auto dir: directions) {
                auto new_dir = dir + cur_dir;
                if (is_inbounds(new_dir) && !seen.contains(new_dir) && garden[new_dir.y][new_dir.x] == '.') {
                    newWorkList.push_back(dir + cur_dir);
                    seen.insert(new_dir);
                    acc++;
                }
            }
        }
        steps[is_odd_step] += acc;
        is_odd_step = !is_odd_step;
        iteration++;
        worklist=newWorkList;
    }
    return steps[!is_odd_step];
}
