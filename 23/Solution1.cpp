//
// Created by floris on 5/23/25.
//


#include <iostream>

#include "Solution.h"

bool Solution::can_pass(char hill, Direction dir) {
    switch (hill) {
        case '>':
            return dir != Direction{1, 0};
        case '<':
            return dir != Direction{-1, 0};
        case '^':
            return dir != Direction{0, -1};
        case 'v':
            return dir != Direction{0, 1};
    }
    throw "this is not supposed to happen";
}


Solution::Direction Solution::get_ice_direction(char hill) {
    switch (hill) {
        case '>':
            return Direction{1, 0};
        case '<':
            return Direction{-1, 0};
        case '^':
            return Direction{0, -1};
        case 'v':
            return Direction{0, 1};
    }
    throw "this is not supposed to happen";
}

void Solution::print_path_taken(state& state) {
    for (int y = 0; y < map_height; ++y) {
        for (int x = 0; x < map_width; ++x) {
            Direction cur_pos{x,y};
            if (state.seen.contains(cur_pos)) {
                std::cout << "O";
            }
            else {
                std::cout << map[y][x];
            }
        }
        std::cout << '\n';
    }
}


int Solution::calculate_solution_1() {
    state begin_state{
        {1,0},
        {1,0},
    0,
        {{1,0}}
    };
    int max_dist{0};

    std::vector<state> work_list{begin_state};
    std::vector<Direction> directions = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0},
    };

    while (!work_list.empty()) {
        state cur_state = *work_list.begin();
        for (auto &dir: directions) {
            char map_loc_cur = map[cur_state.pos.y][cur_state.pos.x];
            if (map_loc_cur != '.' && get_ice_direction(map_loc_cur) != dir) {
                continue;
            }
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

            if (next_pos == end_pos) {
               max_dist = std::max(max_dist,next_state.steps);
                // std::cout << '\n';
                // print_path_taken(next_state);
               continue;
            }

            char map_loc = map[next_pos.y][next_pos.x];
            if (map_loc == '#') {
                continue;
            }
            else {
                work_list.push_back(next_state);
            }



        }

        work_list.erase(work_list.begin());
    }


    return max_dist;
}
