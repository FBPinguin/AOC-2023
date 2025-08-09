//
// Created by floris on 5/23/25.
//


#include <algorithm>
#include <iostream>

#include "Solution.h"

bool Solution::point_inside_square(SandBlock &pos, Position &point) {
    bool point_gt_pos1 = pos.pos1.x <= point.x && pos.pos1.y <= point.y;
    bool point_lt_pos2 = pos.pos2.x >= point.x && pos.pos2.y >= point.y;

    return point_gt_pos1 && point_lt_pos2;
}

bool Solution::same_sector(SandBlock &sb1, SandBlock &sb2) {
    for (int x = sb2.pos1.x; x <= sb2.pos2.x; ++x) {
        for (int y{sb2.pos1.y}; y <= sb2.pos2.y; y++) {
            Position pos{x, y, 0};
            if (point_inside_square(sb1, pos)) {
                return true;
            }
        }
    }

    return false;
}

void Solution::init_sandblock_connections() {
    for (auto &block: sand_blocks) {
        sandblock_connection connection{};
        connection_map[&block] = {};
        for (auto &other_block: sand_blocks) {
            if (&other_block == &block) {
                continue;
            }
            if (same_sector(block, other_block)) {
                connection.connected.push_back(&other_block);
            }
        }
        connection_map[&block] = connection;
    }
}


int Solution::get_highest_y_of_sandblock(SandBlock &sb) {
    int max_val{1};
    auto &[connections, resting_on_count, at_z] = connection_map[&sb];
    if (at_z != 0) {
        return at_z;
    }
    for (auto &connected: connections) {
        if (connected->pos1.z > sb.pos1.z) {
            continue;
        }
        int val = get_highest_y_of_sandblock(*connected);
        int height = std::abs(connected->pos1.z - connected->pos2.z);
        max_val = std::max(max_val, val + height + 1);
    }
    at_z = max_val;


    return max_val;
}

void Solution::calculate_resting_on_count() {
    for (auto &sandblock: sand_blocks) {
        auto &[connections, resting_on, z] = connection_map[&sandblock];
        for (auto &connected: connections) {
            auto &[_, __, at_z] = connection_map[connected];
            int height = std::abs(connected->pos1.z - connected->pos2.z);
            if (at_z+height == z - 1) {
                resting_on++;
                directly_above[connected].push_back(&sandblock);
            }
        }
    }
}

int Solution::calculate_solution_1() {
    init_sandblock_connections();
    for (auto &sandblock: sand_blocks) {
        get_highest_y_of_sandblock(sandblock);
    }

    calculate_resting_on_count();

    int acc{0};

    for (auto &sandblock: sand_blocks) {
        if (!directly_above.contains(&sandblock)) {
            acc++;
            continue;
        }
        for (auto &above: directly_above[&sandblock]) {
            if (connection_map[above].resting_on_count < 2) {
                if (connection_map[above].resting_on_count == 0) {
                    std::cout << "Oh,no";
                }
                goto fail;
            }
        }
        acc++;
    fail:

    }


    return acc;
}
