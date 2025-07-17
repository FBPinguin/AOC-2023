//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <fstream>
#include <map>
#include <unordered_map>
#include <array>
#include <vector>
#include  <utility>

class Solution{

    struct lenses {
        std::string label;
        int hash;
        int focalLength;
        bool removeLabel;
    };

public:
    void init(std::ifstream& input);

    int calculate_solution_1(std::ifstream& input);

    int getLabelHash(std::string label);
    lenses extractLens(std::string lens);


    int calculate_solution_2(std::ifstream& input);
private:
    std::array<std::vector<std::pair<std::string, int>>,256> boxes;

};

#endif //SOLUTION_H
