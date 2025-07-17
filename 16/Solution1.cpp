//
// Created by floris on 5/23/25.
//


#include <iostream>
#include <map>
#include <unordered_set>

#include "Solution.h"

int Solution::calculate_solution_1(std::pair<int,int> pos, dir Dir){
    seen = {};
    beenTo = {};
    moveTowardsDirection(pos, Dir);
    int count = beenTo.size();

    return count;
}


std::map<char, std::map<dir, std::vector<dir>>> dir_map {
      {'/',  {{E, {N   }},
              {N, {E   }},
              {W, {S   }},
              {S, {W   }}}},
      {'\\', {{E, {S   }},
              {N, {W   }},
              {W, {N   }},
              {S, {E   }}}},
      {'-',  {{E, {E   }},
              {N, {E, W}},
              {W, {W   }},
              {S, {E, W}}}},
      {'|',  {{E, {N, S}},
              {N, {N   }},
              {W, {N, S}},
              {S, {S   }}}},
      {'.',  {{E, {E   }},
              {N, {N   }},
              {W, {W   }},
              {S, {S   }}}},
    };

void Solution::moveTowardsDirection(std::pair<int,int> position, dir direction) {
        auto [x, y] = position;

        if (seen.contains({position, direction})) {
            return;
        }

        if (x >= mapCols || y >= mapRows || x < 0 || y < 0) {
            return;
        }

        seen.insert({position, direction});
        beenTo.insert(position);

        for (auto newDir : dir_map[map[y][x]][direction]){
            switch (newDir) {
                case N:
                    moveTowardsDirection({position.first, position.second - 1}, N);
                    break;
                case E:
                    moveTowardsDirection({position.first+1, position.second}, E);
                    break;
                case S:
                    moveTowardsDirection({position.first, position.second + 1}, S);
                    break;
                case W:
                    moveTowardsDirection({position.first-1, position.second}, W);
                    break;
            }
        }
}
