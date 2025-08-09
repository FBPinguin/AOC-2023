//
// Created by floris on 5/23/25.
//


#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Solution.h"
#include "util.h"
Solution::Position Solution::get_position(std::string pos_string) {
   std::stringstream ss{pos_string};
    int x,y,z;
    char garbage;
    ss >> x;
    ss >> garbage;
    ss >> y;
    ss >> garbage;
    ss >> z;
    ss >> garbage;
    // std::cout << std::format("{} + {} + {}\n", x, y ,z);
    return {x,y,z};
}

void Solution::init(std::ifstream& input){

    for (std::string line; std::getline( input, line);) {
        int split_pos = line.find('~');
        Position pos1, pos2;
        pos1 = get_position(line.substr(0, split_pos));
        pos2 = get_position(line.substr(split_pos+1));

        sand_blocks.push_back({pos1,pos2});
    }


}
