//
// Created by floris on 5/23/25.
//


#include <fstream>
#include <iostream>

#include "Solution.h"
#include "util.h"

void Solution::init(std::ifstream& input){
    util::charMap map = util::convertToMap(input);
    this->map = map;
    map_height = map.size();
    map_width = map[0].size();
    end_pos = { (int)map_width-2,(int)map_height-1};
}
