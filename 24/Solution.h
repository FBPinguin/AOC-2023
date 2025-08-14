//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <fstream>
#include <vector>

class Solution{
    struct vec3 {
        long long x;
        long long y;
        long long z;
    };

    struct hailstone {
        vec3 position;
        vec3 velocity;
    };

public:
    void init(std::ifstream& input);

    double get_time_of_collision(hailstone &hs1, hailstone &hs2);

    double hailstone_y(hailstone &hs, double x);

    bool hailstone_collide(hailstone &hs1, hailstone &hs2);

    int calculate_solution_1();

    int calculate_solution_2();

private:
    std::vector<hailstone> all_hailstone;

};

#endif //SOLUTION_H
