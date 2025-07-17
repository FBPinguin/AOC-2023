#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Solution{

public:
    std::vector<std::vector<int>> seqs;

    void init(std::ifstream& input){
        std::string line;
        while (getline(input, line)) {
        std::vector<int> seq;
            std::stringstream ss{line};
            std::string word;
            while (ss >> word) {
                seq.push_back(std::stoi(word));
            }
            seqs.push_back(seq);
        }

    }
    std::vector<int> difference(std::vector<int>& seq) {
        std::vector<int> val;
        for (auto i{0}; i < seq.size()-1; ++i) {
            val.push_back(seq[i+1] - seq[i]);
        }
        return val;
    }

    int getNext(std::vector<int> seq) {
        if (std::ranges::all_of(seq, [](int a){return a==0;})) {
            return 0;
        }

        return seq[seq.size()-1] + getNext(difference(seq));
    }


    int calculate_solution_1(){
        long acc{0};
        for (auto& seq : seqs) {
            acc+= getNext(seq);
        }
        return acc;
    }


    int getPrev(std::vector<int> seq) {
        if (std::ranges::all_of(seq, [](int a){return a==0;})) {
            return 0;
        }

        return seq[0] - getPrev(difference(seq));
    }

    int calculate_solution_2(){
        long acc{0};
        for (auto& seq : seqs) {
            acc+= getPrev(seq);
        }
        return acc;
    }


};

int main (int argc, char *argv[]) {
    Solution solution{};
    std::ifstream file{"input.txt"};
    solution.init(file);
    std::cout << "Solution 1: "<< solution.calculate_solution_1() << '\n';
    std::cout << "Solution 2: "<< solution.calculate_solution_2() << '\n';
    return 0;
}
