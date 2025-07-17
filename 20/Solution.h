//
// Created by floris on 5/23/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H
#include <fstream>
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>
#include <iostream>

class Solution {

    enum Signal {
        high,
        low
    };

    struct SignalTask {
        std::string src;
        std::string dest;
        Signal power;
    };

    enum ModuleType {
        broadcaster,
        flipflop,
        conjunction,
    };

    struct Module {
        std::vector<std::string> out;
        ModuleType type;
        std::unordered_map<std::string, Signal> in;
        bool isOn;
    };

    Module*begin_broadcaster = nullptr;
    std::vector<Module*> all_flipflops;
    std::unordered_map<std::string, Module> all_modules;
    std::vector<SignalTask> work_list;
    std::unordered_map<Signal, int> total_send{{low, 0},{high, 0}};
    int rxCounter{0};


public:
    void init(std::ifstream &input);

    void pushButton();

    void handleTask(const SignalTask & signal_task);

    int calculate_solution_1();

    int calculate_solution_2();
};

#endif //SOLUTION_H
