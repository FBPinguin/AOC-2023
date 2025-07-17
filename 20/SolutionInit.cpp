//
// Created by floris on 5/23/25.
//


#include <fstream>
#include <iostream>
#include <sstream>

#include "Solution.h"
#include "util.h"

void Solution::init(std::ifstream &input) {
    all_modules.clear();
    for (std::string line{}; getline(input, line);) {
        Module curModule{};
        std::string label{};
        if (line[0] == '%') {
            curModule.type = flipflop;
            curModule.isOn = false;
        } else if (line[0] == '&') {
            curModule.type = conjunction;
            curModule.in = {};
        } else {
            curModule.type = broadcaster;
            label = "broadcaster";
        }

        if (curModule.type != broadcaster) {
            label = line.substr(1, line.find(' ')-1);
        }


        std::stringstream inLabels{line.substr(line.find('>') + 1, line.size() - line.find('>'))};
        std::string inLabel{};
        while (inLabels >> inLabel) {
            if (inLabel.ends_with(',')) {
                inLabel.pop_back();
            }
            curModule.out.push_back(inLabel);
        }
        all_modules[label] = curModule;
    }
    for (auto& [label, module] : all_modules) {
        if (module.type == broadcaster) {
         begin_broadcaster = &module;
        }

        for (auto s : module.out) {
            auto& refMod = all_modules[s];
            if (refMod.type == conjunction) {
                refMod.in.insert({label, low});
            }
        }
    }
}



