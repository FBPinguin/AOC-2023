//
// Created by floris on 5/23/25.
//


#include <chrono>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Solution.h"







namespace std {
    template <>
    struct hash<position> {
        std::size_t operator()(const position& p) const {
            std::size_t h1 = std::hash<int>()(p.x);
            std::size_t h2 = std::hash<int>()(p.y);
            // Combine hashes
            return h1 ^ (h2 << 1); // or use boost::hash_combine-like approach
        }
    };
    template <>
    struct hash<std::tuple<position,position,int>> {
        std::size_t operator()(const std::tuple<position,position,int>& p) const {
            std::size_t h1 = std::hash<position>()(std::get<0>(p));
            std::size_t h2 = std::hash<position>()(std::get<1>(p));
            std::size_t h3 = std::hash<int>()(std::get<2>(p));

            // Combine hashes
            return h1 ^ (h2 << 1) ^ (h3 << 4); // or use boost::hash_combine-like approach
        }
    };
}

int Solution::calculate_solution_1(){
    return CalculateShortestPath();
    return minVal;
}

std::vector<position> moves{
        {0,1},
        {0,-1},
        {1,0},
        {-1,0}
};



int Solution::CalculateShortestPath() {
    std::vector<state> work_list{{{0,0}, 0,{},1}};
    std::unordered_map<std::tuple<position, position, int>, int> seen{{{{0,0},{},0},heatMap[0][0]-'0'}};
    int mapCols = heatMap[0].size();
    int mapRows = heatMap.size();

    while (!work_list.empty()) {
        std::sort(work_list.begin(), work_list.end(), [](state& lv, state& rv){return lv.val < rv.val;});
        auto [pos, val, lastMove, numOfMove] = work_list[0];
        for (auto& move : moves) {
            if (move == lastMove*-1) {
                continue;
            }
            position nextPos = pos+move;
            if (nextPos.x < 0 || nextPos.x >= mapCols || nextPos.y < 0 || nextPos.y >= mapRows) {
                continue;
            }
            int curValue = val+heatMap[nextPos.y][nextPos.x]-'0';


            int nextNumOfMove = lastMove == move
                        ? numOfMove + 1
                        : 1;


            if (nextNumOfMove > 3) {
                continue;
            }

            std::tuple key = {nextPos, move, nextNumOfMove};

            if (seen.contains(key) && seen[key] <= curValue) {
                continue;
            }



            seen[key] = curValue;
            work_list.push_back({nextPos, curValue, move, nextNumOfMove});

        }
        work_list.erase(work_list.begin());
    }

    position finalPos{mapCols-1,mapRows-1};
    int lowest{1000000};
    for (auto& [key, val] : seen) {
        auto& [pos, dir, count] = key;
        if (pos == finalPos) {
            lowest = std::min(val, lowest);
        }
    }
    return lowest;

}
