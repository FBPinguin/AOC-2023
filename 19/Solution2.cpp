//
// Created by floris on 5/23/25.
//


#include <algorithm>
#include <bitset>
#include <iostream>

#include "Solution.h"

long long Solution::calcInterval(Solution::itemInterval ii, std::string &next) {
    long long acc{0};

    workflow &curWorlflow = all_workflows[next];
    for (int i = 0; i < curWorlflow.funcs.size(); ++i) {
        auto func = curWorlflow.funcs[i];
        auto &[opp, amount, label, type] = curWorlflow.vals[i];

        itemInterval newInterval{ii};

        if (opp == '>') {
            newInterval.valueMap[type].lower = std::max(newInterval.valueMap[type].lower, amount + 1);
            ii.valueMap[type].upper = std::min(ii.valueMap[type].upper, amount);
        } else if (opp == '<') {
            newInterval.valueMap[type].upper = std::min(newInterval.valueMap[type].upper, amount - 1);
            ii.valueMap[type].lower = std::max(ii.valueMap[type].lower, amount);
        }

        if (invalidRange(newInterval)) {
            continue;
        }


        if (label == "R") {
            continue;
        }
        if (label == "A") {
            acc += calcIntervalSolution(newInterval);
            continue;
        }

        acc += calcInterval(newInterval, label);

        if (invalidRange(ii)) {
            break;
        }


    }

    return acc;
}
long long Solution::calcIntervalSolution(itemInterval ii) {
    if (invalidRange(ii)) return 0;
    const auto& x = ii.valueMap[Categories::x];
    const auto& m = ii.valueMap[Categories::m];
    const auto& a = ii.valueMap[Categories::a];
    const auto& s = ii.valueMap[Categories::s];
    long long x_len = x.upper - x.lower + 1;
    long long m_len = m.upper - m.lower + 1;
    long long a_len = a.upper - a.lower + 1;
    long long s_len = s.upper - s.lower + 1;
    return x_len * m_len * a_len * s_len;
}


bool Solution::invalidRange(const itemInterval &ii) {
    Categories arr[]{x, m, a, s};
    for (auto ctgr: arr) {
        if (ii.valueMap.at(ctgr).lower > ii.valueMap.at(ctgr).upper) {
            return true;
        }
    }
    return false;
}

long long Solution::calculate_solution_2() {
    itemInterval interval{
        {
            {x, {1,  4000}},
            {m, {1, 4000}},
            {a, {1, 4000}},
            {s, {1, 4000}},
        }
    };


    std::string begin{"in"};
    return calcInterval(interval, begin);
}
