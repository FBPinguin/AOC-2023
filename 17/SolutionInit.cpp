//
// Created by floris on 5/23/25.
//


#include <fstream>
#include <iostream>

#include "Solution.h"
#include "util.h"

void Solution::init(std::ifstream& input){
    heatMap = util::convertToMap(input);
}
