//
// Created by floris on 5/23/25.
//

#include "unordered_set"
#include "Solution.h"


int Solution::calculate_solution_2() {
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
    int total_iterations = 26501365;

    int vec_index{0};

    auto modulo = [&](int x, int y) {
        if (x < 0) {
            if (x%y == 0) {
                x--;
            }
            x = x%y;
            return y+x;
        }
        return x%y;
    };

    while (iteration < total_iterations) {
        int acc{0};
        std::vector<Direction> newWorkList;

        for (auto cur_dir: worklist) {
            for (auto dir: directions) {
                auto new_dir = dir + cur_dir;
                int wrapped_y = modulo(new_dir.y,garden.size());
                int wrapped_x = modulo(new_dir.x,garden[0].size());
                if (!seen.contains(new_dir) && garden[wrapped_y][wrapped_x] == '.') {
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