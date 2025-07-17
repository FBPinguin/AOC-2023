

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

class Solution {

  struct record {
    long time;
    long distance;
  };

  std::vector<record> recordData{};
  record recordDatap2{};

public:
  void init(std::ifstream &input) {
    std::string line;
    getline(input, line);
    std::stringstream ss{line};
    std::string word;
    std::string label;
    std::string combinedTime;
    std::string combinedDistance;
    ss >> label;
    while (ss >> word) {
      recordData.push_back(record{std::stoi(word), -1});
      combinedTime += word;
    }
    getline(input, line);
    int i{0};
    ss.clear();
    ss.str("");
    ss << line;
    ss >> label;
    while (ss >> word) {
      recordData[i].distance = std::stoi(word);
      combinedDistance += word;
      i++;
    }
    recordDatap2.distance = std::stol(combinedDistance);
    recordDatap2.time = std::stol(combinedTime);
  }

  long calcDist(long time, long recordTime) {
    return time * (recordTime - time);
  }

  int calculate_solution_1() {
    int acc{1};
    for (record record : recordData) {
      int min, max;
      for (int i{0}; i < record.time; ++i) {
        if (calcDist(i, record.time) > record.distance) {
          min = i;
          break;
        }
      }
      for (long i{record.time}; i > 0; --i) {
        if (calcDist(i, record.time) > record.distance) {
          max = i;
          break;
        }
      }
      acc *= (max - min + 1);
    }
    return acc;
  }

  int calculate_solution_2() {
    int acc{1};
    int min{0}, max{0};
    for (long i{0}; i < recordDatap2.time; ++i) {
      if (calcDist(i, recordDatap2.time) > recordDatap2.distance) {
        min = i;
        break;
      }
    }
    for (long i{recordDatap2.time}; i > 0; --i) {
      if (calcDist(i, recordDatap2.time) > recordDatap2.distance) {
        max = i;
        break;
      }
    }
    return (max - min + 1);
  }
};

int main(int argc, char *argv[]) {
  Solution solution{};
  std::ifstream file{"input.txt"};
  solution.init(file);
  std::cout << solution.calculate_solution_1() << '\n';
  std::cout << solution.calculate_solution_2() << '\n';
  return 0;
}
