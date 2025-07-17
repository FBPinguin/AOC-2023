//
// Created by floris on 6/9/25.
//

#include "util.h"


std::vector<std::vector<char>> util::convertToMap(std::istream& input){
    charMap charMap_return;
    for (std::string line; getline(input, line);) {
        std::vector<char> tempVec;
        for (char c : line) {
            tempVec.push_back(c);
        }
        charMap_return.push_back(tempVec);
    }
    return std::move(charMap_return);
}

std::vector<std::string> util::convertToArr(std::istream& input) {
    stringArr arr_return;
    for (std::string line; getline(input, line);) {
        arr_return.push_back(line);
    }
    return std::move(arr_return);
}