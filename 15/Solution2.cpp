//
// Created by floris on 5/23/25.
//


#include <iostream>
#include <ranges>

#include "Solution.h"

Solution::lenses Solution::extractLens(std::string lens) {
    int currValue{0};
    for (int i = 0; i < lens.length(); ++i) {
        char c = lens[i];
        if (c == '=') {
            int focalLength = std::stoi(lens.substr(i+1, lens.length()-i+1));
            return {lens.substr(0,i), currValue,focalLength, false};
        }
        if (c == '-') {
            return {lens.substr(0,i), currValue
                ,-1, true};
        }
        currValue = ((currValue + c)*17)%256;
    }
    throw "lense oculd not be converted";
}

int Solution::calculate_solution_2(std::ifstream& input){

    for (std::string s; getline(input, s, ',');) {
        lenses lense = extractLens(s);
        if (lense.removeLabel) {
            for (auto p = boxes[lense.hash].begin(); p != boxes[lense.hash].end(); ++p) {
                if (p->first == lense.label) {
                    boxes[lense.hash].erase(p);
                    break;
                }
            }
        }
        else {
            for (auto& [key, value] : boxes[lense.hash]) {
                if (key == lense.label) {
                    value = lense.focalLength;
                    goto skipadd; // I can't be asked making a flip variable
                }
            }
            boxes[lense.hash].push_back({lense.label, lense.focalLength});// = lense.focalLength
            skipadd:
        }
    }

    int acc{0};
    for (int i = 0; i < boxes.size(); ++i) {
        for (int j = 0; j < boxes[i].size(); ++j) {
            acc += (i+1)*(j+1)*boxes[i][j].second;
        }
    }
    return acc;
}
