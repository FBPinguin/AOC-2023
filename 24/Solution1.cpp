//
// Created by floris on 5/23/25.
//


#include <cmath>
#include <format>
#include <iostream>

#include "Solution.h"

double Solution::get_time_of_collision(hailstone &hs1, hailstone &hs2) {
    auto &[pos0, vel0] = hs1;
    auto &[pos1, vel1] = hs2;
    auto [a, b, _] = vel0;
    auto [x0, y0, _d] = pos0;
    auto [c, d, _e] = vel1;
    auto [x1, y1, _f] = pos1;

    double dem = c * b - a * d;
    if (dem == 0) {
        throw "can't divide by zero :-(";
    }

    double num = c * (y1 - y0) - d * (x1 - x0);
    double t = num / dem;

    return t;
}


bool Solution::hailstone_collide(hailstone &hs1, hailstone &hs2) {
    double t, t_b;
    try {
        t = get_time_of_collision(hs1, hs2);
        t_b = get_time_of_collision(hs2, hs1);
    } catch (...) {
        return false;
    }

    if (t < 0 || t_b < 0) {
        return false;
    }
    double x{hs1.velocity.x * t + hs1.position.x};
    double y{hs1.velocity.y * t + hs1.position.y};


    long long lower_bound = 200000000000000;
    long long upper_bound = 400000000000000;
    bool x_inside{x >= lower_bound && x <= upper_bound};
    bool y_inside{y >= lower_bound && y <= upper_bound};

    // std::cout << std::format("x: {} y: {} t: {} {}\n", x, y, t, x_inside && y_inside);
    return x_inside && y_inside;
}

int Solution::calculate_solution_1() {
    int acc{0};
    for (int i = 0; i < all_hailstone.size(); ++i) {
        for (int j = i + 1; j < all_hailstone.size(); ++j) {
            hailstone &hailstone1 = all_hailstone[i];
            hailstone &hailstone2 = all_hailstone[j];
            if (hailstone_collide(hailstone1, hailstone2)) {
                acc++;
            }
        }
    }
    return acc;
}
