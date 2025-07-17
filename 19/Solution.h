//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <fstream>
#include <functional>
#include <unordered_map>
#include <bitset>

class Solution{
public:

    enum Categories {
        m,
        x,
        a,
        s,
    };
    struct Item {
        std::unordered_map<Categories, int> valueMap;
    };

    struct workflow {
        std::vector<std::function<std::string(Item&)>> funcs;
        std::vector<std::tuple<char, int, std::string, Categories>> vals;
    };

    struct interval {
        int lower;
        int upper;
    };

    struct itemInterval {
        std::unordered_map<Categories, interval> valueMap;
    };

    std::unordered_map<std::string, workflow> all_workflows;
    std::vector<Item> all_items;

public:
    void init(std::ifstream& input);

    int calculate_solution_1();


    bool invalidRange(const itemInterval & ii);

    long long calcInterval(itemInterval ii, std::string &next);

    long long calcIntervalSolution(itemInterval ii);

    long long calcIntervalSolutionhelper(itemInterval ii, std::bitset<4> bs, std::array<int, 16>&);

    long long calculate_solution_2();

    Categories to_categorie(char c) {
        switch (c) {
            case 'm':
                return m;
            case 'x':
                return x;
            case 'a':
                return a;
            case 's':
                return s;
            default:
                throw;
        }
    }

    std::string move_through_workflow(workflow& curWorkflow, Item& item) {
        for (auto func : curWorkflow.funcs) {
            std::string answer{func(item)};
            if (answer != "next") {
                return answer;
            }
        }
        return "ERROR";
    }
};

#endif //SOLUTION_H
