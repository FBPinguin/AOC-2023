//
// Created by floris on 5/23/25.
//


#include <fstream>
#include <iostream>
#include <regex>

#include "Solution.h"
#include "util.h"

void Solution::init(std::ifstream &input) {
    for (std::string line; getline(input, line) && !line.empty();) {
        workflow curWorkflow;
        std::string label = line.substr(0, line.find('{'));

        std::regex regexMatch(R"((\w)([<>])(\d+):(\w+))");
        auto regex_begin = std::sregex_iterator{line.begin(), line.end(), regexMatch};
        auto regex_end{std::sregex_iterator()};
        for (std::sregex_iterator i = regex_begin; i != regex_end; i++) {
            std::smatch matches = *i;
            Categories type = to_categorie(matches[1].str()[0]);
            char opp = matches[2].str()[0];
            int amount = std::stoi(matches[3].str());
            std::string dest = matches[4].str();
            curWorkflow.vals.push_back({opp,  amount, dest, type});
            if (opp == '>') {
                curWorkflow.funcs.push_back([amount, dest, type](Item& i) {
                    if (i.valueMap[type] > amount) {
                        return dest;
                    }
                    else {
                        return std::string("next");
                    }
                });
            }
            else if (opp == '<') {
                 curWorkflow.funcs.push_back([amount, dest, type](Item& i) {
                    if (i.valueMap[type] < amount) {
                        return dest;
                    }
                    else {
                        return std::string("next");
                    }
                });
            }
        }

        auto lastCommaPos{line.rfind(',')};
        std::string elseLabel{line.substr(lastCommaPos+1,line.size()-lastCommaPos-2)};
        curWorkflow.funcs.push_back([=](Item& i){return std::string{elseLabel};});
        curWorkflow.vals.push_back({'=',  -1, elseLabel, s});
        all_workflows[label] = curWorkflow;

    }

    for (std::string line; getline(input, line);) {
        Item item;

        std::regex regex{R"(\{x=(\d+),m=(\d+),a=(\d+),s=(\d+)\})"};
        std::smatch matches;

        if (std::regex_match(line, matches, regex)) {
            item.valueMap[x] = std::stoi(matches[1]);
            item.valueMap[m] = std::stoi(matches[2]);
            item.valueMap[a] = std::stoi(matches[3]);
            item.valueMap[s] = std::stoi(matches[4]);
           all_items.push_back(item);
        }


    }
}
