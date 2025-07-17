//
// Created by floris on 5/23/25.
//


#include <fstream>
#include <iostream>
#include <sstream>

#include "Solution.h"
#include "util.h"

void Solution::init(std::ifstream &input) {
    for (std::string line; getline(input, line);) {
        Instruction curInstruction;
        std::stringstream lineSS{line};
        std::string dir;
        lineSS >> dir;
        char charDir{dir[0]};
        switch (charDir) {
            case 'R':
                curInstruction.direction = right;
                break;
            case 'D':
                curInstruction.direction = down;
                break;
            case 'L':
                curInstruction.direction = left;
                break;
            case 'U':
                curInstruction.direction = up;
                break;
        }

        std::string nTimes;
        lineSS >> nTimes;
        curInstruction.nSteps = std::stoi(nTimes);

        std::string hexCode;
        lineSS >> hexCode;
        hexCode.erase(0,2);
        hexCode.pop_back();
        hexCode.insert(0, "0x");

        curInstruction.hexColor = std::stoi(hexCode, 0, 16);


        instructions.push_back(curInstruction);
    }

    input.clear();
    input.seekg(0, std::ios::beg);

    for (std::string line; getline(input, line);) {
        Instruction curInstruction;
        std::stringstream lineSS{line};
        std::string garbage;
        lineSS >> garbage;
        lineSS >> garbage;

        std::string hexCode;
        lineSS >> hexCode;
        hexCode.erase(0,2);
        hexCode.pop_back();
        hexCode.insert(0, "0x");
        int direction = hexCode[hexCode.size()-1]-'0';
        hexCode.pop_back();
        switch (direction) {
            case 0:
                curInstruction.direction = right;
                break;
            case 1:
                curInstruction.direction = down;
                break;
            case 2:
                curInstruction.direction = left;
                break;
            case 3:
                curInstruction.direction = up;
                break;
        }
        curInstruction.nSteps = std::stoi(hexCode, 0, 16);
        curInstruction.hexColor = -1;


        instructions_p2.push_back(curInstruction);
    }

}
