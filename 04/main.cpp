

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
class Solution {
  std::vector<std::unordered_set<int>> winning{};
  std::vector<std::vector<int>> cards{};

public:
  void init(std::ifstream &input) {
    std::string line;
    while (std::getline(input, line)) {
      std::stringstream ss{line};
      std::string word;
      while (ss >> word) {
        if (word.ends_with(':')) {
          break;
        }
      }
      std::unordered_set<int> set{};
      while (ss >> word) {
        if (word == "|") {
          winning.push_back(set);
          break;
        }
        set.insert(std::stoi(word));
      }
      std::vector<int> card{};
      while (ss >> word) {
        card.push_back(std::stoi(word));
      }
      cards.push_back(card);
    }
  }

  int calculate_solution_1() {
    int total_points{0};
    for (int i{0}; i < cards.size(); ++i) {
      int curr_worth{0};
      for (int j{0}; j < cards[i].size(); ++j) {
        if (winning[i].contains(cards[i][j])) {
          if (curr_worth == 0) {
            ++curr_worth;
          } else {
            curr_worth *= 2;
          }
        }
      }
      total_points += curr_worth;
    }
    return total_points;
  }
  int calculate_solution_2(){
    std::unordered_map<int, int> copys{};
    for (int i{0}; i < cards.size(); ++i) {
      int curr_copy{0};
      for (int j{0}; j < cards[i].size(); ++j) {
        if (winning[i].contains(cards[i][j])) {
          curr_copy++;
        }
      }
      int end{i+1+curr_copy};
      for (int start{i+1}; start < end;start++ ){
        copys[start] += (1+copys[i]);
      }
    }
    int acc{0};
    for (int i{0}; i < cards.size(); ++i){
      acc += copys[i] + 1;
    }
    return acc;
  }
};

int main(int argc, char *argv[]) {
  std::ifstream input{"input.txt"};
  auto start = std::chrono::high_resolution_clock::now();
  Solution solution{};
  solution.init(input);
  std::cout << "Solution 1: " << solution.calculate_solution_1() << '\n';
  std::cout << solution.calculate_solution_2() << '\n';
  auto end  = std::chrono::high_resolution_clock::now();
  std::cout << (end - start) << '\n';
  return 0;
}
