//
// Created by floris on 5/23/25.
//


#include <fstream>
#include <iostream>
#include <sstream>

#include "Solution.h"
#include "util.h"

void Solution::init(std::ifstream& input){
    for (std::string line; std::getline(input, line);) {
       long long posx, posy, posz, velx, vely, velz;
        std::stringstream ss{line};
        char garbage;

        ss >> posx;
        ss >> garbage;
        ss >> posy;
        ss >> garbage;
        ss >> posz;
        ss >> garbage;
        ss >> velx;
        ss >> garbage;
        ss >> vely;
        ss >> garbage;
        ss >> velz;

        hailstone new_hailstone{
            {posx,posy,posz},
        {velx,vely,velz}};
        all_hailstone.push_back(new_hailstone);
    }
}
