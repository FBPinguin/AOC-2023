//
// Created by floris on 5/23/25.
//


#include <iostream>
#include <queue>

#include "Solution.h"

int Solution::calculate_solution_2() {
    state begin_state{
        {1,0},
        {1,0},
    0,
        {{1,0}}
    };
    int max_dist{0};

    // std::vector<state> work_list{begin_state};
    auto cmp = [](const state& left, const state& right) {
        return left.steps>right.steps;
    };
    std::priority_queue<state, std::vector<state>,decltype(cmp)> work_list;
    work_list.emplace(begin_state);
    std::vector<Direction> directions = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0},
    };

    std::unordered_map<Direction, int, DirectionHash> value_map;

    while (!work_list.empty()) {
        state cur_state = work_list.top();

        work_list.pop();
        for (auto &dir: directions) {


            Direction next_pos = {cur_state.pos.x + dir.x, cur_state.pos.y + dir.y};
            state next_state = {
                next_pos,
                dir,
                cur_state.steps + 1,
                cur_state.seen
            };
            next_state.seen.insert(next_pos);

            if (cur_state.seen.contains(next_pos)) {
                continue;
            }

            if (next_pos.x >= map_width || next_pos.y >= map_height) {
                continue;
            }

            if (next_pos.x < 0 || next_pos.y < 0) {
                continue;
            }

            if (value_map.contains(next_pos)) {
               if (value_map[next_pos] > next_state.steps) {
                   continue;
               }
            }
            else {
                value_map[next_pos] = next_state.steps;
            }

            if (next_pos == end_pos) {
               max_dist = std::max(max_dist,next_state.steps);
                // print_path_taken(next_state);
               continue;
            }

            char map_loc = map[next_pos.y][next_pos.x];
            if (map_loc == '#') {
                continue;
            }
            else {
                work_list.emplace(next_state);
                std::cout << next_state.steps << '\n';
            }



        }

    }


    return max_dist;
}
