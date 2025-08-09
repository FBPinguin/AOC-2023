//
// Created by floris on 5/23/25.
//


#include <unordered_set>

#include "Solution.h"

void Solution::count_blocks_depending_on(SandBlock& block, std::unordered_set<SandBlock*>& amount, std::unordered_map<SandBlock *, sandblock_connection> &
                                         connection_map) {
    if (!directly_above.contains(&block)) {
        return;
    }
    for (auto& above : directly_above[&block]) {
        connection_map[above].resting_on_count--;
        if (connection_map[above].resting_on_count <= 0) {
            if (!amount.contains(above)) {
                amount.insert(above);
                count_blocks_depending_on(*above,amount, connection_map);
            }
        }
    }
}

int Solution::calculate_solution_2(){

    int acc{0};
    for (auto& block : sand_blocks) {
        std::unordered_set<SandBlock*> result;

    std::unordered_map<SandBlock*, sandblock_connection> connection_map_copy = connection_map;
        count_blocks_depending_on(block, result, connection_map_copy);

        acc += result.size();
    }

    return acc;
}
