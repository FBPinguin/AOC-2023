//
// Created by floris on 6/9/25.
//

#ifndef UTIL_H
#define UTIL_H
#include <istream>
#include <vector>
#include "util.h"


namespace util {

    typedef std::vector<std::vector<char>> charMap;
    typedef std::vector<std::string> stringArr;


    charMap convertToMap(std::istream& input);
    stringArr convertToArr(std::istream& input);
}

#endif //UTIL_H
