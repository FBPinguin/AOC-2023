#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

class Solution{

public:
    std::string instructions;
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;
    std::vector<std::string> startPos;
    int steps{0};
    int instructPointer{0};
    void init(std::ifstream& input){
        // set Instructions
        getline(input, instructions);
        std::string line;
        getline(input, line);
        while (getline(input, line)) {
            std::string key, lv, rv;
            std::string word;
            std::stringstream ss{line};
            std::string buff;
            ss >> key;
            ss >> buff;
            ss >> lv;
            lv = lv.substr(1, lv.size()-2);
            ss >> rv;
            rv = rv.substr(0, rv.size()-1);
            if (key.ends_with('A')) {
                startPos.push_back(key);
            }
            map[key] = std::pair{lv,rv};
        }
    }

    void followMap(std::pair<std::string, std::string>& value) {
        std::string val;
        ++steps;
        if (instructions[instructPointer] == 'L') {
            val = value.first;
        }
        else {
            val = value.second;
        }
        instructPointer = (instructPointer + 1) % instructions.size();
        if (val == "ZZZ") {
            return;
        }
        return followMap(map[val]);

    }

    int calculate_solution_1(){

        followMap(map["AAA"]);

        return steps;
    }

    void nextPos(std::string& curPos) {
        std::string val;
        if (instructions[instructPointer] == 'L') {
            val = map[curPos].first;
        }
        else {
            val = map[curPos].second;
        }
        curPos = val;
    }

    long LCM(long a, long b)
    {
        long greater = std::max(a, b);
        long smallest = std::min(a, b);
        for (long i = greater; ; i += greater) {
            if (i % smallest  == 0)
                return i;
        }
    }


    long calculate_solution_2(){
        std::vector<int> loops;
        for (auto& pos : startPos) {
            steps = 0;
            while (!pos.ends_with('Z')) {
                steps++;
                nextPos(pos);
                instructPointer = (instructPointer + 1) % instructions.size();
            }
            loops.push_back(steps);
            instructPointer = 0;
            steps=0;
        }
        long currLCM{0};
        for (int loop : loops) {
            if (currLCM == 0) {
                currLCM = loop;
            }
            currLCM = LCM(currLCM, loop);

        }

        return currLCM;
    }


};

int main (int argc, char *argv[]) {
    Solution solution{};
    std::ifstream file{"input.txt"};
    solution.init(file);
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << solution.calculate_solution_1() << '\n';
    std::cout << solution.calculate_solution_2() << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) << '\n';
    return 0;
}
