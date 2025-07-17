//
// Created by floris on 5/23/25.
//


#include <chrono>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Solution.h"


namespace std {
    template<>
    struct hash<position> {
        std::size_t operator()(const position &p) const {
            std::size_t h1 = std::hash<int>()(p.x);
            std::size_t h2 = std::hash<int>()(p.y);
            // Combine hashes
            return h1 ^ (h2 << 1); // or use boost::hash_combine-like approach
        }
    };

    template<>
    struct hash<std::tuple<position, position, int> > {
        std::size_t operator()(const std::tuple<position, position, int> &p) const {
            std::size_t h1 = std::hash<position>()(std::get<0>(p));
            std::size_t h2 = std::hash<position>()(std::get<1>(p));
            std::size_t h3 = std::hash<int>()(std::get<2>(p));

            // Combine hashes
            return h1 ^ (h2 << 1) ^ (h3 << 4); // or use boost::hash_combine-like approach
        }
    };
}



std::vector<position> moves2{
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};


bool Solution::isValidPos(const __gnu_cxx::__alloc_traits<std::allocator<state> >::value_type &value, position move) {
    int nextX{value.pos.x + move.x};
    int nextY{value.pos.y + move.y};
    if (nextX < 0 || nextX >= heatMap[0].size()) {
        return false;
    }
    if (nextY < 0 || nextY >= heatMap.size()) {
        return false;
    }
    return true;
}


int Solution::calculate_solution_2() {
    auto cmp = [](state &left, state &right) { return left.val > right.val; };
    std::priority_queue<state, std::vector<state>, decltype(cmp)> work_list{};
    std::unordered_map<std::tuple<position, position, int>, int> seen{{{{0,0},{},0},heatMap[0][0]-'0'}};

    work_list.push({{0, 0}, 0, {0, 1}, 0});
    work_list.push({{0, 0}, 0, {1, 0}, 0});

    while (!work_list.empty()) {
        auto curState = work_list.top();
        work_list.pop();

        std::tuple cacheKey{curState.pos, curState.lastMove, curState.numOfMove};
        if (seen.contains(cacheKey) && seen[cacheKey] < curState.val) {
            continue;
        }

        seen[cacheKey] = curState.val;


        for (auto &move: moves2) {
            if (isValidPos(curState, move)) {
                position nextPos{curState.pos.x + move.x, curState.pos.y + move.y};
                int nextVal{curState.val + (heatMap[nextPos.y][nextPos.x] - '0')};
                int nextMoveCounter{0};

                position inverseLastMove{curState.lastMove.x*-1, curState.lastMove.y*-1};
                if (move == inverseLastMove) {
                    continue;
                }
                if (move == curState.lastMove) {
                    nextMoveCounter = curState.numOfMove + 1;
                }
                else if (curState.numOfMove > 9 || curState.numOfMove < 3) {
                    continue;
                }

                if (curState.pos.y == heatMap.size() - 1 && curState.pos.x == heatMap[0].size() - 1) {
                    return curState.val;
                }
                state nextState{{nextPos}, nextVal, move, nextMoveCounter};
                work_list.push(nextState);
            }
        }
    }
}